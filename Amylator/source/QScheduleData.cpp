#include "QScheduleData.h"


#include <iostream>

namespace {
     bool comparePtrToEntry(QScheduleEntry* a, QScheduleEntry* b) 
     { 
         return (*a < *b); 
     }
}

QScheduleData::QScheduleData(QObject *parent)
: QObject(parent)
{
    add(1, 30);
    add(3, 40);
    add(2, 50);
}

//---------------------------------------------------------------------

QScheduleData::QEntryList QScheduleData::entries()  
{ 
    return QQmlListProperty<QScheduleEntry>(this, _entries); 
}

//---------------------------------------------------------------------

void QScheduleData::sort()
{
    std::sort(_entries.begin(), _entries.end(), comparePtrToEntry);
}

//---------------------------------------------------------------------

void QScheduleData::add(int duration, int temperature)
{
    auto* entry = new QScheduleEntry();
    entry->duration(duration);
    entry->temperature(temperature);
    _entries.push_back(entry);
    sort();

    Q_EMIT entriesChanged();
}

//---------------------------------------------------------------------

void QScheduleData::edit(int index, int duration, int temperature)
{
    _entries[index]->duration(duration);
    _entries[index]->temperature(temperature);
    sort();

    Q_EMIT entriesChanged();
}

//---------------------------------------------------------------------

void QScheduleData::clear()
{
    _entries.clear();
    Q_EMIT entriesChanged();
}

//---------------------------------------------------------------------

QScheduleData::MashSteps QScheduleData::mashSteps() const
{
    MashSteps mashSteps;
    for (const auto* e : _entries)
    {
        auto dur  = std::chrono::minutes(e->duration());
        auto step = MashStep(e->temperature(), dur);
        mashSteps.push_back(step);  
    }

    return mashSteps;
}

