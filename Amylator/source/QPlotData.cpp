#include "QPlotData.h"

#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>

#include <iostream>


QPlotData::QPlotData(QObject *parent)
: QObject(parent)
{
}

//---------------------------------------------------------------------

void QPlotData::add(const MashLogs& logs)
{
    if (_series) 
    {
        QtCharts::QLineSeries *lineSeries = static_cast<QtCharts::QLineSeries *>(_series);
        for (auto& log : logs)
        {
            lineSeries->append(_axisCounter/(2*60.f), log.temperature());
            ++_axisCounter;
        }
    }
}

//---------------------------------------------------------------------

void QPlotData::clear()
{
    QtCharts::QLineSeries *lineSeries = static_cast<QtCharts::QLineSeries *>(_series);
    lineSeries->clear();
    _axisCounter = 0;
}

//---------------------------------------------------------------------

int QPlotData::xMin() const { return _xMin; }
int QPlotData::xMax() const { return _xMax; }
int QPlotData::yMin() const { return _yMin; }
int QPlotData::yMax() const { return _yMax; }

//---------------------------------------------------------------------

void QPlotData::updateAxis()
{
    bool needUpdate = false;
    
    if (needUpdate)
    {
        Q_EMIT xMinChanged();
        Q_EMIT xMaxChanged();
        Q_EMIT yMinChanged();
        Q_EMIT yMaxChanged();
    }
}

//---------------------------------------------------------------------


