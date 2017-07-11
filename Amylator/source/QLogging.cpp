#include "QLogging.h"
#include <QtCore/QTimer>
#include <iostream>


QString QLogging::_text = QString();
bool QLogging::_changed = false;

//---------------------------------------------------------------------

QLogging::QLogging(QObject *parent) 
: QObject(parent) 
{
    qInstallMessageHandler( QLogging::myMessageHandler );

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QLogging::update);
    timer->start(50);
}

//---------------------------------------------------------------------

QString QLogging::text() const
{
    return _text;
}

//---------------------------------------------------------------------

void QLogging::clear()
{
    _text = QString();
    _changed = true;
}

//---------------------------------------------------------------------

void QLogging::update()
{
    if (_changed)
    {
        _changed = false;
        Q_EMIT textChanged();
    }
}

//---------------------------------------------------------------------

void QLogging::myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    switch (type) 
    {
        case QtDebugMsg:    txt = QString("Debug: %1\n").arg(msg); break;
        case QtWarningMsg:  txt = QString("Warning: %1\n").arg(msg); break;
        case QtCriticalMsg: txt = QString("Critical: %1\n").arg(msg); break;
        case QtFatalMsg:    txt = QString("Fatal: %1\n").arg(msg); break;
        case QtInfoMsg:     txt = QString("Info: %1\n").arg(msg); break;
    }

    std::cout << txt.toStdString().c_str() << std::flush;
    _text.append(txt);
    _changed = true;
}

