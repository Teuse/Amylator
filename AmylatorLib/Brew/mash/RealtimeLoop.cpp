#include "RealtimeLoop.h"

#include <algorithm>
#include <boost/format.hpp>

#include <portaudio.h>


namespace brew { namespace mash {

  PaStream* _stream;

//-----------------------------------------------------------------------------
    
namespace 
{
    int audioCallback(const void*, void *outputBuffer, unsigned long frames,
            const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *userData )
    {
        auto callback  = (std::function<void()>*)userData;
        (*callback)();

        // make sure to silent the output
        auto out = (float*)outputBuffer;
        std::fill(out, out+frames,0.f);

        return paContinue;
    }
}


//-----------------------------------------------------------------------------

RealtimeLoop::RealtimeLoop(size_t sampleRate)
{
    auto err = Pa_Initialize();
    if(err != paNoError)
    {
        auto msg = boost::str(boost::format("Failed to initialize PortAudio: %s") % Pa_GetErrorText(err));
        throw std::runtime_error( msg );
    }

    err = Pa_OpenDefaultStream(&_stream, 0, 1, paFloat32, double(sampleRate), 1,
                               audioCallback, &_playbackCallback);
    if( err != paNoError )
    {
        auto msg = boost::str(boost::format("Failed to open Stream: %s") % Pa_GetErrorText(err));
        throw std::runtime_error( msg );
    }
}

RealtimeLoop::~RealtimeLoop() 
{ 
    Pa_CloseStream( _stream ); 
    Pa_Terminate(); 
}

//-----------------------------------------------------------------------------

void RealtimeLoop::start(Callback f)
{
    if (_running) return;
    _playbackCallback = f;

    PaError err = Pa_StartStream( _stream );
    if ( err == paNoError ) 
        _running = true;
    else
    {
        auto msg = boost::str(boost::format("Failed starting Stream: %s") % Pa_GetErrorText(err));
        throw std::runtime_error( msg );
    }
}

//-----------------------------------------------------------------------------

void RealtimeLoop::stop()
{
    if (!_running) return;

    PaError err = Pa_StopStream( _stream );
    if( err != paNoError )
    {
        auto msg = boost::str(boost::format("Failed to stop Stream: %s") % Pa_GetErrorText(err));
        throw std::runtime_error( msg );
    }
    _running = false;
}

//-----------------------------------------------------------------------------

}}

