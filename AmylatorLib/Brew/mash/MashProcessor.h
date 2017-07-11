#pragma once
#include <Brew/data/MashStep.h>

#include <vector>
#include <atomic>

namespace brew { namespace mash {

//-----------------------------------------------------------------------------
    
class MashProcessor
{
    using MashSteps = std::vector<data::MashStep>;

    enum Process 
    {
        PROCESS_OFF,
        PROCESS_START,
        PROCESS_PREPARE_STEP,
        PROCESS_STEP,
        PROCESS_STOP
    };


public:

    MashProcessor();
    ~MashProcessor();

    void start(const MashSteps&);
    void stop();

    auto isRunning()     const -> bool;
    auto isHeating()     const -> bool;
    auto stepIndex()     const -> int;

    // --- Realtime Rendering
    void process(float temperature, clock::Timestamp ts);

private:

    void processStart();
    void processStop();
    void processStepPreparation(float temperature, clock::Timestamp ts);
    void processStep(float temperature, clock::Timestamp ts);

    void setHeater(bool state);

    MashSteps            _steps;
    clock::Timestamp     _stepStartTime;
    std::atomic<Process> _process   = { PROCESS_OFF };
    std::atomic<int>     _stepIndex = { -1 };
    std::atomic<bool>    _isHeating = { false };
};

}}

