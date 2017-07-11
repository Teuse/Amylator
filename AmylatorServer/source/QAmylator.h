#pragma once
#include <QServer.h>
#include <QConsoleReader.h>
#include <Brew/mash/MashController.h>
#include <Brew/data/Message.h>

#include <QObject>


class QAmylator : public QObject
{
    Q_OBJECT

public:
    QAmylator(QObject *parent = nullptr, bool disableGPIO=false);


private slots:
    void onMsgReceived(brew::data::Message, network::ClientID);
    void processInput(QConsoleReader::Command, QConsoleReader::Argument);

private:

    void runLoop();
    void processRequests();


    brew::mash::MashController _mashController;

    QConsoleReader* _consoleReader;
    QServer*       _server;
    bool           _relayState   = false;


signals:
    // connected from outside!
    void quitApplication(); 
};

