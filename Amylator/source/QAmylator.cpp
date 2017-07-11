#include "QAmylator.h"

#include <Brew/data/Message.h>
#include <iostream>


QAmylator::QAmylator(QObject *parent)
: QObject(parent)
, _running(false)
, _currentStep(-1)
, _client(new QClient(this))
, _plotData(new QPlotData(this))
, _scheduleData(new QScheduleData(this))
{
    connect(_client, SIGNAL(messageReceived(brew::data::Message)), this, SLOT(onMsgReceived(brew::data::Message)));
}

//----------------------------------------------------------------------------------

void QAmylator::onMsgReceived(brew::data::Message msg)
{
    using namespace brew::data;
    for (auto req : msg.mashRequests())
    {
        switch(req.type())
        {
            case MashRequest::TYPE_SET_LOG_FULL:
                _plotData->clear();
            case MashRequest::TYPE_SET_LOG_UPDATE:
                _plotData->add(msg.mashLogs());    
                break;
            default: break;
        }
    }

    if (msg.hasMashLogs())
    {
        const auto& lastLog = msg.mashLogs().back();

        auto running = lastLog.isProcessing();
        if (running != _running)
        {
            std::cout << "Running: " << std::boolalpha << running << std::endl;
            _running = running;
            Q_EMIT runningChanged();
        }

        auto curStep = running ? lastLog.scheduleIndex() : -1;
        if (curStep != _currentStep)
        {
            _currentStep = curStep;
            Q_EMIT currentStepChanged();
        }
    }
}

//----------------------------------------------------------------------------------

void QAmylator::start()
{
    using namespace brew::data;
    Message message;
    message.addMashRequest(MashRequest::TYPE_SET_START_MASH);
    message.setMashSteps(_scheduleData->mashSteps());
    _client->sendMessage(message);
}

//---------------------------------------------------------------------

void QAmylator::pause()
{
    using namespace brew::data;
    Message message;
    message.addMashRequest(MashRequest::TYPE_SET_PAUSE_MASH);
    _client->sendMessage(message);
}

//---------------------------------------------------------------------

void QAmylator::stop()
{
    using namespace brew::data;
    Message message;
    message.addMashRequest(MashRequest::TYPE_SET_STOP_MASH);
    _client->sendMessage(message);
}

//---------------------------------------------------------------------

void QAmylator::reload()
{
    using namespace brew::data;
    Message message;
    message.addMashRequest(MashRequest::TYPE_GET_LOG_FULL);
    _client->sendMessage(message);
}

//----------------------------------------------------------------------------------

bool           QAmylator::running()      const { return _running; }
int            QAmylator::currentStep()  const { return _currentStep; }
QString        QAmylator::version()      const { return QString("%1.%2").arg(kAppVersion, kBuildVersion); }
QClient*       QAmylator::client()       const { return _client; }
QPlotData*     QAmylator::plotData()     const { return _plotData; }
QScheduleData* QAmylator::scheduleData() const { return _scheduleData; }
