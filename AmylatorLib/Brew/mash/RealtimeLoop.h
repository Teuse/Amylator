#pragma once
#include <functional>


namespace brew { namespace mash {

//-----------------------------------------------------------------------------

class RealtimeLoop 
{
  using Callback = std::function<void()>;


public:

  RealtimeLoop(size_t sampleRate);
  ~RealtimeLoop();

  void start(Callback f);
  void stop();
  bool isRunning() const { return _running; }


private:

  bool      _running = false;
  Callback  _playbackCallback;
};

}}

