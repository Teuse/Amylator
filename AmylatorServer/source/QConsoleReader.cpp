#include "QConsoleReader.h"
#include <QTextStream>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <iostream>
#include <unistd.h> //Provides STDIN_FILENO

QConsoleReader::QConsoleReader(QObject *parent) 
: QObject(parent)
, _notifier(STDIN_FILENO, QSocketNotifier::Read)
{
    _commandMap["quit"] = COMMAND_QUIT;
    _commandMap["exit"] = COMMAND_QUIT;
    _commandMap["version"] = COMMAND_VERSION;
    _commandMap["relay_on"] = COMMAND_RELAY_ON;
    _commandMap["relay_off"] = COMMAND_RELAY_OFF;
    _commandMap["temperature"] = COMMAND_TEMPERATURE;
    _commandMap["temp"] = COMMAND_TEMPERATURE;

    connect(&_notifier, SIGNAL(activated(int)), this, SLOT(text()));
}

void QConsoleReader::text()
{
    QTextStream qin(stdin);
    QString line = qin.readLine();
    processInput(line.toStdString());
}

//---------------------------------------------------------------------

void QConsoleReader::processInput(std::string input)
{
    std::vector<std::string> words;
    boost::split(words, input, boost::is_any_of(" "));
    if (words.empty() || words[0].length() == 0 || words[0] == " ") return;

    auto it = _commandMap.find(words[0]);
    if (it != _commandMap.end())
    {
        Q_EMIT textReceived(it->second, QConsoleReader::Argument());
    }
    else {
        std::cout << "ConsoleReader: command not found: " << words[0] << std::endl;
    }
}

bool QConsoleReader::parseBool(std::string word)
{

    return true;
}

