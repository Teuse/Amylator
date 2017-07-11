#pragma once
#include <Brew/data/MashLog.h>

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>

class QPlotData : public QObject 
{
   Q_OBJECT
   Q_PROPERTY(int xMin    READ xMin   NOTIFY xMinChanged)
   Q_PROPERTY(int xMax    READ xMax   NOTIFY xMaxChanged)
   Q_PROPERTY(int yMin    READ yMin   NOTIFY yMinChanged)
   Q_PROPERTY(int yMax    READ yMax   NOTIFY yMaxChanged)
   
   using MashLogs = std::vector<brew::data::MashLog>;
   
public:
   explicit QPlotData(QObject *parent = nullptr);

   void add(const MashLogs&);
   void clear();
   
   int           xMin() const;
   Q_SIGNAL void xMinChanged();
   int           xMax() const;
   Q_SIGNAL void xMaxChanged();
   int           yMin() const;
   Q_SIGNAL void yMinChanged();
   int           yMax() const;
   Q_SIGNAL void yMaxChanged();
   
   Q_INVOKABLE void setSeries(QtCharts::QAbstractSeries* series) { _series = series; }

   
private:

   void updateAxis();

   int      _axisCounter = 0;
   QtCharts::QAbstractSeries *_series;
   int      _xMin = 0;
   int      _xMax = 0;
   int      _yMin = 0;
   int      _yMax = 0;
   
};

