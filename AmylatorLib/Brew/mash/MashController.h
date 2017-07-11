#pragma once
#include <Brew/mash/MashProcessor.h>
#include <Brew/mash/RealtimeLoop.h>

#include <Brew/data/MashStep.h>
#include <Brew/data/MashLog.h>

#include <GPIO/Pin.h>
#include <GPIO/Sensors.h>

#include <boost/lockfree/spsc_queue.hpp>
#include <memory>


namespace brew { namespace mash {

//-----------------------------------------------------------------------------
    
class MashController
{
    using Queue     = boost::lockfree::spsc_queue<brew::data::MashLog>;
    using MashLogs  = std::vector<brew::data::MashLog>;
    using MashSteps = std::vector<brew::data::MashStep>;


public:
    MashController(bool disableGPIO);
    ~MashController();

    void start(const MashSteps&);
    void stop();

    auto getChangeLogs()     -> MashLogs;
    auto getFullProcessLog() -> MashLogs;

    void  setHeater(bool on);
    float temperature();


private:

    void realtimeLoop();
    void consumeLogs();
    void updateGPIO(bool isRunning, bool isHeating);


    bool          _gpioDisabled = false;
    MashProcessor _mashProcessor;
    RealtimeLoop  _realtimeLoop;
    int           _rtCounter = 0;
    bool          _isHeatingManual = false;

    MashLogs    _changeLogs;
    MashLogs    _processLogs;
    Queue       _logQueue;

    std::unique_ptr<gpio::Pin>    _greenLed    = nullptr;
    std::unique_ptr<gpio::Pin>    _yellowLed   = nullptr;
    std::unique_ptr<gpio::Pin>    _redLed      = nullptr;
    std::unique_ptr<gpio::Pin>    _heaterRelay = nullptr;
};

}}

