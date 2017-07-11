#include "QServer.h"
#include <Brew/Config.h>

#include <QtCore/QTimer>

#include <iostream>


//-----------------------------------------------------------------------------

QServer::QServer(QObject *parent) 
: QObject(parent) 
, _server(brew::cfg::port)
{
    _server.connectConnectionCount([this](size_t count)      
            { onConnectionCount(count); });
    _server.connectErrorEmitted([](std::string error)        
            { std::cout << "Server error: " << error << std::endl; });
    _server.connectDataReceived([this](std::string dataStr, network::ClientID id)  
            { onDataReceived(dataStr, id); });

    _zcPublisher.connectError([this](zeroconf::Error e){ onPublishError(e); });

    QTimer* networkTimer = new QTimer(this);
    connect(networkTimer, &QTimer::timeout, this, &QServer::updateNetwork);
    networkTimer->start(33);

    using namespace brew::cfg;
    _zcPublisher.start("Amylator", serviceType, "local", port);
    _server.start();
}

//-----------------------------------------------------------------------------

void QServer::updateNetwork()
{
    _server.poll();
    _zcPublisher.poll();
}

//-----------------------------------------------------------------------------

void QServer::sendMessage(brew::data::Message msg, network::ClientID id)
{
    if (id > 0) {
        _server.send(msg.exportToString(), id); 
    }
    else {
        //Broadcast
        _server.send(msg.exportToString());
    }
}

//-----------------------------------------------------------------------------

void QServer::onDataReceived(std::string dataStr, network::ClientID id)
{
    brew::data::Message message;
    message.importAsString(dataStr);

    Q_EMIT messageReceived(message, id);
}

//-----------------------------------------------------------------------------

void QServer::onConnectionCount(size_t count)
{
    std::cout << "ConnectionCountChanged: " << count << std::endl;
}

//-----------------------------------------------------------------------------

void QServer::onPublishError(zeroconf::Error e)
{
    std::cout << "Publish zeroconf service failed with error: " << e << std::endl;
}

