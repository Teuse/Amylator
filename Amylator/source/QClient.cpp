#include "QClient.h"

#include <Brew/Config.h>

#include <QtCore/QTimer>
#include <iostream>


//----------------------------------------------------------------------------------

namespace 
{
    std::string nameForState(network::ConnectionState state)
    {
        using namespace network;
        switch (state) {
            case STATE_OFF:        return "STATE OFF";  break;
            case STATE_CONNECTING: return "CONNECTING"; break;
            case STATE_CONNECTED:  return "CONNECTED";  break;
        }
        return "Unknown state";
    }
}

//----------------------------------------------------------------------------------

QClient::QClient(QObject *parent) 
: QObject(parent) 
, _client(brew::cfg::port)
{
    _client.connectConnectionChanged([this](network::ConnectionState state) { onConnectionStateChanged(state); });
    _client.connectDataReceived([this](std::string msg)                     { onDataReceived(msg); });
    _client.connectErrorEmitted([](std::string error)                       { std::cout << "Client error: " << error << std::endl; });

    _zcBrowser.connectServiceAdded([this](zeroconf::ServicePtr s)            { onServiceAdded(s); });
    _zcBrowser.connectServiceUpdated([this](zeroconf::ServicePtr s)          { onServiceRemoved(s); });
    _zcBrowser.connectError([this](zeroconf::Error e)                        { onBrowserError(e); });

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QClient::updateNetwork);
    timer->start(33);

    _zcBrowser.start(brew::cfg::serviceType);
}

//----------------------------------------------------------------------------------

void QClient::updateNetwork()
{
    _client.poll();
    _zcBrowser.poll();
}

//---------------------------------------------------------------------

bool QClient::connected() const
{
    using cs = network::ConnectionState;
    return _client.connectionState() == cs::STATE_CONNECTED;
}

//----------------------------------------------------------------------------------

void QClient::sendMessage(brew::data::Message msg)
{
    using cs = network::ConnectionState;
    if (_client.connectionState() == cs::STATE_CONNECTED)
    {
        _client.send(msg.exportToString());
    }
}

//----------------------------------------------------------------------------------

void QClient::onDataReceived(std::string dataStr)
{
    brew::data::Message message;
    message.importAsString(dataStr);

    Q_EMIT messageReceived(message);
}

//----------------------------------------------------------------------------------

void QClient::onConnectionStateChanged(network::ConnectionState state)
{
    std::cout << "ConnectionStateChanged: " << nameForState(state) << std::endl;
    using cs = network::ConnectionState;

    if (state == cs::STATE_OFF || state == cs::STATE_CONNECTED)
    {
        Q_EMIT connectedChanged();
    }

    if (state == cs::STATE_OFF)
    {
        _zcBrowser.start(brew::cfg::serviceType.c_str());
    }
}

//----------------------------------------------------------------------------------

void QClient::onServiceAdded(zeroconf::ServicePtr zcs)
{
    std::cout << "onServiceAddes: " << zcs->name << " " << zcs->address << std::endl;
    _zcBrowser.stop();

    _client.connect(zcs->address);
}

//----------------------------------------------------------------------------------

void QClient::onServiceRemoved(zeroconf::ServicePtr zcs)
{
    std::cout << "onServiceRemoved: " << zcs->name << std::endl;
}

//----------------------------------------------------------------------------------

void QClient::onBrowserError(zeroconf::Error e)
{
    std::cout << "Browse zeroconf service failed with error: " << e << std::endl;
}

//----------------------------------------------------------------------------------

