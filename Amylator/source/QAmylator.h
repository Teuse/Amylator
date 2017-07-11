#pragma once
#include <QClient.h>
#include <QPlotData.h>
#include <QScheduleData.h>

#include <Brew/data/Message.h>

#include <QtCore/QObject>
#include <QObject>
#include <QString>


class QAmylator : public QObject 
{
    Q_OBJECT
    Q_PROPERTY(bool           running      READ running               NOTIFY runningChanged)
    Q_PROPERTY(int            currentStep  READ currentStep           NOTIFY currentStepChanged)
    Q_PROPERTY(QString        version      READ version               NOTIFY versionChanged)
    Q_PROPERTY(QClient*       client       READ client                NOTIFY clientChanged)
    Q_PROPERTY(QPlotData*     plotData     READ plotData              NOTIFY plotDataChanged)
    Q_PROPERTY(QScheduleData* scheduleData READ scheduleData          NOTIFY scheduleDataChanged)
   
public:
    explicit QAmylator(QObject *parent = nullptr);

    bool running() const;
    Q_SIGNAL void runningChanged();

    int currentStep() const;
    Q_SIGNAL void currentStepChanged();
    
    QString version() const;
    Q_SIGNAL void versionChanged();

    QClient* client() const;
    Q_SIGNAL void clientChanged();

    QPlotData* plotData() const;
    Q_SIGNAL void plotDataChanged();

    QScheduleData* scheduleData() const;
    Q_SIGNAL void scheduleDataChanged();

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void reload();


private slots:
    void onMsgReceived(brew::data::Message);

private:
   
    bool           _running;
    int            _currentStep;
    QClient*       _client;
    QPlotData*     _plotData;
    QScheduleData* _scheduleData;

};

