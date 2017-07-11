#pragma once
#include <QObject>
#include <QSocketNotifier>
#include <map>
#include <string>


//-----------------------------------------------------------------------------
//TODO: Bring QSocketNotifier into small helper class and make this class a
//      non Qt class

class QConsoleReader : public QObject
{
    Q_OBJECT

public:

    enum Command 
    {
        COMMAND_NONE,
        COMMAND_QUIT,
        COMMAND_VERSION,
        COMMAND_TEMPERATURE,
        COMMAND_RELAY_ON,
        COMMAND_RELAY_OFF
    };
    
    struct Details 
    {
        enum Argument { NONE, BOOL, INT, FLOAT };

        Details(Command c, Argument a, std::string h) 
            : command(c), argument(a), helpText(h) {}

        Command     command  = COMMAND_NONE;
        Argument    argument = NONE;
        std::string helpText;
    };

    struct Argument {
        bool        bolean = false;
        int         number = 0;
        float       decimal = 0.f;
    };

    explicit QConsoleReader(QObject *parent = 0);

signals:
    void textReceived(QConsoleReader::Command, QConsoleReader::Argument);

public slots:
        void text();

private:
    void processInput(std::string);
    bool parseBool(std::string);

    QSocketNotifier _notifier;

    using CommandMap = std::map<std::string, Command>;
    CommandMap  _commandMap;
};
