#include "QAmylator.h"

#include <Brew/data/MashStep.h>
#include <Brew/data/MashRequest.h>
#include <Brew/data/MashLog.h>

#include <QtCore/QTimer>

#include <iostream>


QAmylator::QAmylator(QObject *parent, bool disableGPIO) 
: QObject(parent) 
, _server(new QServer(this))
, _consoleReader(new QConsoleReader(this))
, _mashController(disableGPIO)
{
    connect(_server, SIGNAL(messageReceived(brew::data::Message, network::ClientID)), 
            this, SLOT(onMsgReceived(brew::data::Message, network::ClientID)));

    connect(_consoleReader, SIGNAL(textReceived(QConsoleReader::Command, QConsoleReader::Argument)), this, SLOT(processInput(QConsoleReader::Command, QConsoleReader::Argument)));

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QAmylator::runLoop);
    timer->start(100);
}

//----------------------------------------------------------------------------------

void QAmylator::runLoop()
{
    using namespace brew::data;
    auto logs = _mashController.getChangeLogs();

    Message msg; 
    msg.addMashRequest(MashRequest::TYPE_SET_LOG_UPDATE);
    msg.setMashLogs( logs );
    _server->sendMessage(msg);
}

//----------------------------------------------------------------------------------

void QAmylator::onMsgReceived(brew::data::Message msg, network::ClientID id)
{
    using namespace brew::data;
    Message outMsg; 

    for (auto req : msg.mashRequests())
    {
        switch(req.type())
        {
            case MashRequest::TYPE_GET_LOG_FULL:
            {
                auto logs = _mashController.getFullProcessLog();
                outMsg.addMashRequest(MashRequest::TYPE_SET_LOG_FULL);
                outMsg.setMashLogs( logs );
                break;
            }
            case MashRequest::TYPE_SET_START_MASH:
            {
                assert(msg.hasMashSteps());
                _mashController.start(msg.mashSteps());
                break;
            }
            case MashRequest::TYPE_SET_STOP_MASH:
            {
                _mashController.stop();
                break;
            }
            case MashRequest::TYPE_SET_PAUSE_MASH:
            {
                // _mashController.pause();
                break;
            }
            default: break;
        }
    }

    if (outMsg.hasMashRequests())
        _server->sendMessage(outMsg);
}

//---------------------------------------------------------------------

void QAmylator::processInput(QConsoleReader::Command command, QConsoleReader::Argument arg)
{
    switch (command)
    {
        case QConsoleReader::COMMAND_QUIT:         { quitApplication(); break; }
        case QConsoleReader::COMMAND_VERSION:      { std::cout << "Version: " << kAppVersion << "." << kBuildVersion << std::endl; break; }
        case QConsoleReader::COMMAND_RELAY_ON:     { std::cout << "switch relay on"  << std::endl; _mashController.setHeater(true); break; }
        case QConsoleReader::COMMAND_RELAY_OFF:    { std::cout << "switch relay off" << std::endl; _mashController.setHeater(false); break; } 
        case QConsoleReader::COMMAND_TEMPERATURE:  { std::cout << "Temperature: " << _mashController.temperature() << " °C" << std::endl; break; } 
        default: std::cout << "QConsoleReader Command not implemented!" << std::endl;
    }
}

