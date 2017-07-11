
set(APP_VERSION   "1.0")
set(BUILD_VERSION "0")

##  --------------------------------------------------------------------------------------
##  Find Packages
##  --------------------------------------------------------------------------------------
find_package(Boost       COMPONENTS system serialization)
find_package(Qt5Core     REQUIRED)
find_package(Qt5Charts   REQUIRED)
find_package(Qt5Gui      REQUIRED)
find_package(Qt5Quick    REQUIRED)
find_package(Qt5Qml      REQUIRED)
find_package(Qt5Widgets  REQUIRED)
find_package(Qt5Svg      REQUIRED)

##  --------------------------------------------------------------------------------------
##  Source Files
##  --------------------------------------------------------------------------------------
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(FILES_ROOT ${SRC_ROOT}/main.cpp
               ${SRC_ROOT}/QAmylator.h      ${SRC_ROOT}/QAmylator.cpp
               ${SRC_ROOT}/QClient.h        ${SRC_ROOT}/QClient.cpp
               ${SRC_ROOT}/QScheduleData.h  ${SRC_ROOT}/QScheduleData.cpp
               ${SRC_ROOT}/QPlotData.h      ${SRC_ROOT}/QPlotData.cpp
               ${SRC_ROOT}/QLogging.h       ${SRC_ROOT}/QLogging.cpp)
source_group("App" FILES ${FILES_ROOT})

##  --------------------------------------------------------------------------------------
##  MOC Files
##  --------------------------------------------------------------------------------------
set(FILES_MOC_H ${SRC_ROOT}/QAmylator.h
                ${SRC_ROOT}/QClient.h
                ${SRC_ROOT}/QScheduleData.h
                ${SRC_ROOT}/QPlotData.h
                ${SRC_ROOT}/QLogging.h)
qt5_wrap_cpp(FILES_MOC_SRC ${FILES_MOC_H})

##  --------------------------------------------------------------------------------------
##   Resource Files
##  --------------------------------------------------------------------------------------
set(QRCResources resources/images.qrc
                 resources/qml.qrc)

qt5_add_resources(QRCComiledResources ${QRCResources} )
source_group("Resources\\qrc" FILES ${QRCResources})

file(GLOB_RECURSE QMLFiles resources/qml/*.qml)
source_group("Resources\\qml" FILES ${QMLFiles})

file(GLOB_RECURSE IMGFiles resources/images/*.*)
source_group("Resources\\images" FILES ${IMGFiles})

set(FILE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/Amylator.icns)
set_source_files_properties(${FILE_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

##  --------------------------------------------------------------------------------------
##   Create Executable
##  --------------------------------------------------------------------------------------
set(FILES_ALL ${FILES_ROOT} ${FILES_MOC_H} ${FILES_MOC_SRC} ${QRCComiledResources}
              ${QMLFiles} ${FILE_ICON})

if(APPLE)
 add_executable(Amylator MACOSX_BUNDLE ${FILES_ALL})
elseif(WIN32)
 add_executable(Amylator WIN32 ${FILES_ALL})
elseif(UNIX)
  add_executable(Amylator ${FILES_ALL})
endif()

target_compile_definitions(Amylator PRIVATE
    kAppVersion="${APP_VERSION}"
    kBuildVersion="${BUILD_VERSION}")

##  --------------------------------------------------------------------------------------
##   Dependencies
##  --------------------------------------------------------------------------------------
qt5_use_modules(Amylator Core Charts Gui Quick Svg Qml Widgets)

target_include_directories(Amylator PUBLIC source)
target_include_directories(Amylator PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(Amylator AmylatorLib NetworkLib ZeroconfLib)
target_link_libraries(Amylator ${Boost_LIBRARIES})

if(APPLE)
  target_link_libraries(Amylator "-framework OpenGL" )
endif()

##  --------------------------------------------------------------------------------------
##  Configure Info.plist - Mac
##  --------------------------------------------------------------------------------------
if(APPLE)
    set_target_properties(Amylator PROPERTIES
       MACOSX_BUNDLE_INFO_PLIST            "${CMAKE_CURRENT_SOURCE_DIR}/resources/cfg/MacOSXBundleInfo.plist"
       MACOSX_BUNDLE_BUNDLE_VERSION        "${APP_VERSION}"
       MACOSX_BUNDLE_SHORT_VERSION_STRING  "${APP_VERSION}"
       MACOSX_BUNDLE_LONG_VERSION_STRING   "${APP_VERSION}.${BUILD_VERSION}"
       MACOSX_BUNDLE_INFO_STRING           "${APP_VERSION}, Copyright © 2015 Mathias Roder"
       MACOSX_BUNDLE_BUNDLE_NAME           "Amylator"
       MACOSX_BUNDLE_ICON_FILE             "Amylator.icns"
       MACOSX_BUNDLE_GUI_IDENTIFIER        "com.teuse.amylator"
       MACOSX_BUNDLE_COPYRIGHT             "Mathias Roder"
     )
     set_bundle_key( Amylator CFBundleExecutable Amylator )
endif()
