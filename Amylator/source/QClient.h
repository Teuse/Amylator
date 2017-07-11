#pragma once
#include <Brew/data/Message.h>

#include <Zeroconf/Browser.h>
#include <Network/Client.h>

#include <QObject>


class QClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected      READ connected               NOTIFY connectedChanged)

public:
    explicit QClient(QObject *parent = nullptr);

    void sendMessage(brew::data::Message);

    bool connected() const;
    Q_SIGNAL void connectedChanged();

signals:
    void messageReceived(brew::data::Message);

private:
    void runLoop();
    void updateNetwork();
    void onDataReceived(std::string);
    void onConnectionStateChanged(network::ConnectionState);

    void onBrowserError(zeroconf::Error);
    void onServiceAdded(zeroconf::ServicePtr);
	void onServiceRemoved(zeroconf::ServicePtr);


    network::Client    _client;
    zeroconf::Browser  _zcBrowser;
};


