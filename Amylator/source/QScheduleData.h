#pragma once
#include <Brew/data/MashStep.h>

#include <QtCore/QObject>
#include <QList>
#include <QQmlListProperty>

//---------------------------------------------------------------------

class QScheduleEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int  duration    READ duration    WRITE duration    NOTIFY durationChanged)
    Q_PROPERTY(int  temperature READ temperature WRITE temperature NOTIFY temperatureChanged)

public:
   explicit QScheduleEntry(QObject *parent = nullptr) : QObject(parent)  { }

   void duration(int dur) { _dur = dur; }
   int duration() const   { return _dur; }
   Q_SIGNAL void durationChanged();

   void temperature(int temp) { _temp = temp; }
   int temperature() const   { return _temp; }
   Q_SIGNAL void temperatureChanged();

   bool operator < (const QScheduleEntry& other) { return _temp < other._temp; }


private:
   int _dur  = 0;
   int _temp = 0;
};

//---------------------------------------------------------------------

class QScheduleData : public QObject 
{
   Q_OBJECT
   Q_PROPERTY(QQmlListProperty<QScheduleEntry> entries    READ entries   NOTIFY entriesChanged)
   
   using MashStep   = brew::data::MashStep;
   using MashSteps  = std::vector<MashStep>;
   using QEntryList = QQmlListProperty<QScheduleEntry>;
   
public:
   explicit QScheduleData(QObject *parent = nullptr);

   MashSteps mashSteps() const; 

   QEntryList entries(); 
   Q_SIGNAL void entriesChanged();

   Q_INVOKABLE void add(int duration, int temperature);
   Q_INVOKABLE void edit(int index, int duration, int temperature);
   Q_INVOKABLE void clear();


private:

   void sort();

   QList<QScheduleEntry*> _entries;
   
};

