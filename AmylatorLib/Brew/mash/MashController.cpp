#include "MashController.h"
#include <Brew/Config.h>

#include <iostream>
#include <cassert>


namespace brew { namespace mash {
    
//-----------------------------------------------------------------------------
    
namespace cfg 
{
    const int greenLedPin = 4;
    const int yellowLedPin = 5;
    const int redLedPin = 6;
    const int heaterRelayPin = 7;

    namespace rt 
    {
        const float sampleRate    = 5000.f; // Hz
        const float processPeriod = 0.5; // Sec
    }
}

//-----------------------------------------------------------------------------

MashController::MashController(bool disableGPIO)
: _gpioDisabled(disableGPIO)
, _realtimeLoop(cfg::rt::sampleRate)
, _logQueue(200)
{
    if (!disableGPIO)
    {
        _greenLed    = std::make_unique<gpio::Pin>(cfg::greenLedPin, gpio::Pin::Output);
        _yellowLed   = std::make_unique<gpio::Pin>(cfg::yellowLedPin, gpio::Pin::Output);
        _redLed      = std::make_unique<gpio::Pin>(cfg::redLedPin, gpio::Pin::Output);
        _heaterRelay = std::make_unique<gpio::Pin>(cfg::heaterRelayPin, gpio::Pin::Output);
    }

    const auto maxSamples = int(cfg::rt::sampleRate * cfg::rt::processPeriod);
    _realtimeLoop.start([this, maxSamples]()
    { 
        if (++_rtCounter >= maxSamples) {
            realtimeLoop(); 
            _rtCounter = 0;
        }
    });
}

MashController::~MashController()
{
    _realtimeLoop.stop();
}

//-----------------------------------------------------------------------------

void MashController::start(const MashSteps& steps)
{
    _isHeatingManual = false;
    _processLogs.clear();
    _mashProcessor.start(steps);
}

void MashController::stop()
{
    _mashProcessor.stop();
}

//-----------------------------------------------------------------------------

MashController::MashLogs MashController::getChangeLogs()
{
    consumeLogs();
    MashLogs logs;
    logs.swap(_changeLogs);
    return logs;
}

MashController::MashLogs MashController::getFullProcessLog()
{
    consumeLogs();
    return _processLogs;
}

//-----------------------------------------------------------------------------

void MashController::consumeLogs()
{
    _logQueue.consume_all([this](const brew::data::MashLog& log)
    { 
        _changeLogs.push_back(log); 
        if (log.isProcessing())
            _processLogs.push_back(log);
    });
}

//-----------------------------------------------------------------------------

void MashController::setHeater(bool on)
{
    if (_mashProcessor.isRunning()) {
        std::cout << "Can't set relay state manual because the schedule is running!" << std::endl;
    }
    else {
        _isHeatingManual = on;
    }
}

//-----------------------------------------------------------------------------

void MashController::realtimeLoop()
{
    auto ts   = std::chrono::system_clock::now();
    auto temp = temperature();

    _mashProcessor.process(temp, ts);

    auto isHeating = _mashProcessor.isHeating();
    auto stepIndex = _mashProcessor.stepIndex();
    auto isRunning = _mashProcessor.isRunning();

    // Manual Heating doesn't work while processing
    assert( !(isRunning && _isHeatingManual) );
    // Heater must be OFF when process is not running
    assert( !(!isRunning && isHeating) );

    auto log = brew::data::MashLog(temp, isHeating, ts, stepIndex);
    _logQueue.push(log);

    updateGPIO(isRunning, isHeating);
}

//-----------------------------------------------------------------------------
//--- GPIO access
//-----------------------------------------------------------------------------

void MashController::updateGPIO(bool isRunning, bool isHeating)
{
    static bool run  = false;
    static bool heat = false;
    static bool man  = false;

    if (isRunning != run || heat != isHeating || man != _isHeatingManual)
    {
        if (!_gpioDisabled)
        {
            _heaterRelay->set( (isRunning && isHeating) || (_isHeatingManual && !isRunning) );

            _greenLed->set(!isRunning && !_isHeatingManual);
            _yellowLed->set(isRunning && !isHeating);
            _redLed->set(isRunning && isHeating);
        }
        else if (!isRunning && !_isHeatingManual) {
            std::cout << "MashController: LED = green   Heater = off" << std::endl;
        }
        else if (!isRunning && _isHeatingManual) {
            std::cout << "MashController: LED = green   Heater = on " << std::endl;
        }
        else if (isRunning && !isHeating) {
            std::cout << "MashController: LED = yellow  Heater = off" << std::endl;
        }
        else if (isRunning && isHeating) {
            std::cout << "MashController: LED = red     Heater = on " << std::endl;
        }

        run = isRunning;
        heat = isHeating;
        man = _isHeatingManual;
    }
}

//-----------------------------------------------------------------------------

float MashController::temperature()
{
    if (_gpioDisabled)
    {
        static int temp = 20;

        if (_mashProcessor.isHeating())
            ++temp;

        return float(temp);
    }

    return gpio::Sensors::temperature();
}

}}

