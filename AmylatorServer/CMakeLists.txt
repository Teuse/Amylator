set(APP_VERSION   "1.0")
set(BUILD_VERSION "0")

##  --------------------------------------------------------------------------------------
##  Find Packages
##  --------------------------------------------------------------------------------------
find_package(Boost       COMPONENTS system serialization program_options)
find_package(Qt5Core     REQUIRED)

##  --------------------------------------------------------------------------------------
##  Source Files
##  --------------------------------------------------------------------------------------
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(FILES_ROOT ${SRC_ROOT}/main.cpp
               ${SRC_ROOT}/QAmylator.h       ${SRC_ROOT}/QAmylator.cpp
               ${SRC_ROOT}/QServer.h         ${SRC_ROOT}/QServer.cpp
               ${SRC_ROOT}/QConsoleReader.h  ${SRC_ROOT}/QConsoleReader.cpp)
source_group("App" FILES ${FILES_ROOT})

##  --------------------------------------------------------------------------------------
##  MOC Files
##  ---------------------------------------------------------------------------------------
set(FILES_MOC_H ${SRC_ROOT}/QAmylator.h
                ${SRC_ROOT}/QServer.h
                ${SRC_ROOT}/QConsoleReader.h)
qt5_wrap_cpp(FILES_MOC_SRC ${FILES_MOC_H})

##  --------------------------------------------------------------------------------------
##   Create Executable
##  --------------------------------------------------------------------------------------
set(FILES_ALL ${FILES_ROOT} ${FILES_MOC_H} ${FILES_MOC_SRC})

add_executable(AmylatorServer ${FILES_ALL})

target_compile_definitions(AmylatorServer PRIVATE
    kAppVersion="${APP_VERSION}"
    kBuildVersion="${BUILD_VERSION}")

##  --------------------------------------------------------------------------------------
##   Dependencies
##  --------------------------------------------------------------------------------------
qt5_use_modules(AmylatorServer Core)

target_include_directories(AmylatorServer PUBLIC source)
target_include_directories(AmylatorServer PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(AmylatorServer AmylatorLib NetworkLib ZeroconfLib ${Boost_LIBRARIES})

if (UNIX AND NOT APPLE)
    target_link_libraries(AmylatorServer pthread)
endif()
