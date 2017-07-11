#include <QAmylator.h>
#include <QClient.h>
#include <QPlotData.h>
#include <QScheduleData.h>
#include <QLogging.h>

#include <QtCore>
#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QIcon>

#include <boost/predef.h>


//------------------------------------------------------------------------------------------------

void loadComponents()
{
   qmlRegisterType< QAmylator      > ("BrewComponent",   1, 0, "Amylator"   );
   qmlRegisterType< QClient        > ("BrewComponent",   1, 0, "Client"        );
   qmlRegisterType< QPlotData      > ("BrewComponent",   1, 0, "PlotData"      );
   qmlRegisterType< QScheduleData  > ("BrewComponent",   1, 0, "ScheduleData"  );
   qmlRegisterType< QScheduleEntry > ("BrewComponent",   1, 0, "ScheduleEntry" );
   qmlRegisterType< QLogging       > ("BrewComponent",   1, 0, "Logging" );
}

//------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
#if BOOST_OS_WINDOWS
   // Force the Qt renderer to run in a separate thread (this is default behavior on Mac).
   qputenv("QSG_RENDER_LOOP", QByteArray("threaded"));
#endif
   
   QApplication app(argc, argv);
   app.setApplicationVersion( QString("0.1") );
   app.setWindowIcon(QIcon(":/icons/Amylator.ico"));
   
   loadComponents();
   
   QQmlApplicationEngine engine;
   // engine.addImportPath(":/QtGraphicalEffects"); // for QtGraphicalEffects
   engine.load( QUrl("qrc:///qml/main.qml") );
   
   return app.exec();
}

