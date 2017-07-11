#pragma once
#include <Brew/data/Message.h>

#include <Zeroconf/Publisher.h>
#include <Network/Server.h>

#include <QObject>

//-----------------------------------------------------------------------------

class QServer : public QObject
{
    Q_OBJECT

public:
    QServer(QObject *parent = nullptr);

    void sendMessage(brew::data::Message, network::ClientID id=0);

signals:
    void messageReceived(brew::data::Message, network::ClientID id);


private:

    void runLoop();
    void updateNetwork();
    void onDataReceived(std::string, network::ClientID);
    void onConnectionCount(size_t);
    void onPublishError(zeroconf::Error);

    network::Server     _server;
    zeroconf::Publisher _zcPublisher;
};

