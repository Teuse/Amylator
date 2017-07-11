#include <QAmylator.h>
#include <QtCore>

#include <boost/program_options.hpp>

#include <iostream>


//---------------------------------------------------------------------

int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    
    po::options_description description("Usage of Amylator");
    description.add_options()
        ("help,h",    "Display this help message")
        ("version,v", "Display the version number")
        ("testing",   "Disables the GPIO usage and uses dummy values for testing");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).run(), vm);
    po::notify(vm);

    if(vm.count("help"))    { std::cout << description << std::endl; return 0; }
    if(vm.count("version")) { std::cout << kAppVersion << std::endl; return 0; }

    auto disableGPIO = bool(vm.count("testing"));

    //---------------------------------------------------------------------
    
    QCoreApplication app(argc, argv);

    QAmylator *amylator = new QAmylator(&app, disableGPIO);

    QObject::connect(amylator, &QAmylator::quitApplication, &QCoreApplication::quit);

    return app.exec();
}

