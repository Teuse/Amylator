#include "MashProcessor.h"


namespace brew { namespace mash {

//-----------------------------------------------------------------------------
    
MashProcessor::MashProcessor()
{}

MashProcessor::~MashProcessor()
{
    stop();
}

//-----------------------------------------------------------------------------

void MashProcessor::start(const MashSteps& steps)
{
    if (!isRunning())
    {
        _steps = steps;
        _process = PROCESS_START;
    }
}

//-----------------------------------------------------------------------------

void MashProcessor::stop()
{
    _process = PROCESS_STOP;
    setHeater(false); 
}

//-----------------------------------------------------------------------------

bool MashProcessor::isRunning() const { return _process != PROCESS_OFF; }
bool MashProcessor::isHeating() const { return _isHeating; }
int  MashProcessor::stepIndex() const { return _stepIndex; }

//-----------------------------------------------------------------------------

void MashProcessor::setHeater(bool on){  _isHeating = on; }


//-----------------------------------------------------------------------------
//--- Background
//-----------------------------------------------------------------------------

void MashProcessor::process(float temperature, clock::Timestamp ts)
{
    if      (_process == PROCESS_START)        { processStart();           }
    else if (_process == PROCESS_STOP)         { processStop();            }
    else if (_process == PROCESS_PREPARE_STEP) { processStepPreparation(temperature, ts); }
    else if (_process == PROCESS_STEP)         { processStep(temperature, ts);            }
}

//-----------------------------------------------------------------------------

void MashProcessor::processStart()
{
    _stepIndex = 0;
    _process   = PROCESS_PREPARE_STEP;
}

//-----------------------------------------------------------------------------

void MashProcessor::processStop()
{
    _process = PROCESS_OFF;
    _stepIndex = -1;

    setHeater(false);
}

//-----------------------------------------------------------------------------

void MashProcessor::processStepPreparation(float temperature, clock::Timestamp ts)
{
    auto step = _steps[_stepIndex];
    
    if (temperature >= step.temperature())
    {
        _process = PROCESS_STEP;
        _stepStartTime = ts;
        setHeater(false);
    }
    else 
    {
        setHeater(true);
    }
}

//-----------------------------------------------------------------------------

void MashProcessor::processStep(float temperature, clock::Timestamp ts)
{
    using namespace std::chrono;

    auto step         = _steps[_stepIndex];
    auto stepElapsed  = duration_cast<milliseconds>(ts - _stepStartTime);
    auto stepDuration = duration_cast<milliseconds>(step.duration());

    if (stepElapsed > stepDuration)
    {
        ++_stepIndex;
        _process = (_stepIndex <_steps.size()) ? PROCESS_PREPARE_STEP : PROCESS_STOP;
    }
    else if (temperature <= step.temperature() - 1)
    {
        setHeater(true);
    }
    else if (temperature >= step.temperature())
    {
        setHeater(false);
    }
}

//-----------------------------------------------------------------------------

}}

