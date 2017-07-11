
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#--------------------------------------------------------------------
#--- Find Packages
#--------------------------------------------------------------------
if (NOT IOS)
    find_package(Boost      COMPONENTS serialization)
    find_package(Portaudio  REQUIRED)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PORTAUDIO_DEFINITIONS}")
else()
    set(Boost_INCLUDE_DIRS "${BOOST_IOS_ROOT}/include")
    set(Boost_LIBRARIES "libboost_serialization.a")
    link_directories("${BOOST_IOS_ROOT}/lib")
endif()

#--------------------------------------------------------------------
#--- Collecting all files
#--------------------------------------------------------------------
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Brew)

set(FILES_ROOT ${SRC_ROOT}/Config.h)
source_group("Brew" FILES ${FILES_ROOT})


set(FILES_DATA  ${SRC_ROOT}/data/Message.h       ${SRC_ROOT}/data/Message.cpp
                ${SRC_ROOT}/data/MashLog.h       ${SRC_ROOT}/data/MashLog.cpp
                ${SRC_ROOT}/data/MashRequest.h   ${SRC_ROOT}/data/MashRequest.cpp
                ${SRC_ROOT}/data/MashStep.h      ${SRC_ROOT}/data/MashStep.cpp)
source_group("Brew\\data" FILES ${FILES_DATA})

set(FILES_MASH ${SRC_ROOT}/mash/MashController.h  ${SRC_ROOT}/mash/MashController.cpp
               ${SRC_ROOT}/mash/MashProcessor.h   ${SRC_ROOT}/mash/MashProcessor.cpp
               ${SRC_ROOT}/mash/RealtimeLoop.h )
if (IOS)
    list(APPEND FILES_MASH ${SRC_ROOT}/mash/RealtimeLoop-ios.cpp)
else()
    list(APPEND FILES_MASH ${SRC_ROOT}/mash/RealtimeLoop.cpp)
endif()
source_group("Brew\\mash" FILES ${FILES_MASH})

#--------------------------------------------------------------------
#--- Setup Library
#--------------------------------------------------------------------
add_library(AmylatorLib STATIC ${FILES_ROOT} ${FILES_DATA} ${FILES_MASH})

set_target_properties(AmylatorLib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(AmylatorLib PUBLIC . ${Boost_INCLUDE_DIRS})
target_link_libraries(AmylatorLib PUBLIC GPIOLib ${Boost_LIBRARIES})

if (NOT IOS)
    target_include_directories(AmylatorLib PUBLIC ${PORTAUDIO_INCLUDE_DIRS})
    target_link_libraries(AmylatorLib PUBLIC      ${PORTAUDIO_LIBRARIES})
endif()
