TARGET   = Amylator 

# ------------------------------------------------------------------------------
# --- Configure Build
# ------------------------------------------------------------------------------

QT += qml \
      quick \
      widgets

CONFIG += c++14

QMAKE_CXXFLAGS += -fobjc-arc

    ios_icon.files = $$files($$_PRO_FILE_PWD_/resources/icons/Amylator.icns)
    QMAKE_BUNDLE_DATA += ios_icon

    app_launch_images.files = $$files($$_PRO_FILE_PWD_/resources/ios/Default*.png)
    QMAKE_BUNDLE_DATA += app_launch_images

    QMAKE_ASSET_CATALOGS += $$_PRO_FILE_PWD_/resources/ios/Assets.xcassets

    QMAKE_INFO_PLIST = $$_PRO_FILE_PWD_/resources/ios/Info.plist

    QMAKE_IOS_DEPLOYMENT_TARGET = 10.3
    QMAKE_IOS_TARGETED_DEVICE_FAMILY = "1,2"

# ------------------------------------------------------------------------------
# --- Collect files
# ------------------------------------------------------------------------------
DEFINES += kAppVersion="1.0" \
           kBuildVersion="0"


INCLUDEPATH += $$_PRO_FILE_PWD_/source \
               $$_PRO_FILE_PWD_/../BrewLib \
               $$_PRO_FILE_PWD_/../libs/ZeroconfLib \
               $$_PRO_FILE_PWD_/../libs/NetworkLib \
               $$_PRO_FILE_PWD_/../libs/GPIOLib

HEADERS += source/QAmylator.h \
           source/QClient.h \
          source/QLogging.h \
          source/QPlotData.h \
          source/QScheduleData.h

SOURCES += source/main.cpp \
           source/QAmylator.cpp \
           source/QClient.cpp \
           source/QLogging.cpp \
           source/QPlotData.cpp \
           source/QScheduleData.cpp


RESOURCES += resources/qml.qrc \
             resources/images.qrc

# ------------------------------------------------------------------------------
# --- Dependencies
# ------------------------------------------------------------------------------

INCLUDEPATH +=   $$_PRO_FILE_PWD_/../../boost-ios/build/boost/1.64.0/ios/prefix/include
LIBS        += -L$$_PRO_FILE_PWD_/../../boost-ios/build/boost/1.64.0/ios/prefix/lib
LIBS        += -L$$_PRO_FILE_PWD_/../../build-ios/BrewLib/Release-iphoneos
LIBS        += -L$$_PRO_FILE_PWD_/../../build-ios/GPIOLib-binary/Release-iphoneos
LIBS        += -L$$_PRO_FILE_PWD_/../../build-ios/NetworkLib-binary/Release-iphoneos
LIBS        += -L$$_PRO_FILE_PWD_/../../build-ios/ZeroconfLib-binary/Release-iphoneos

LIBS += -lboost_serialization
LIBS += -lboost_system
LIBS += -lBrewLib
LIBS += -lNetworkLib
LIBS += -lGPIOLib
LIBS += -lZeroconfLib
