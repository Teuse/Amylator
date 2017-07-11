if (CMAKE_SETUP_LOADED)
    return()
endif()

set(CMAKE_SETUP_LOADED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")

#-------------------------------------------------------------------------------

if (NOT QT_ROOT_PATH)
    set(QT_ROOT_PATH "/Applications/Qt/5.8")
endif()

if (NOT BOOST_IOS_ROOT)
    set(BOOST_IOS_ROOT "${CMAKE_SOURCE_DIR}/../boost-ios/build/boost/1.64.0/ios/prefix")
endif()

#-------------------------------------------------------------------------------

if (IOS)
    message(STATUS "--- Build for iOS ---")
    set(CMAKE_PREFIX_PATH       ${CMAKE_PREFIX_PATH} "${QT_ROOT_PATH}/ios")
    set(CMAKE_MODULE_PATH       ${CMAKE_MODULE_PATH} "${QT_ROOT_PATH}/ios/lib/cmake/Qt5")

    add_definitions(-DQ_OS_IOS)
    if (IOS_DEVICE)
        add_definitions(-DQ_OS_IOS_DEVICE)
    elseif(IOS_SIMULATOR)
        add_definitions(-DQ_OS_IOS_SIMULATOR)
    endif()

    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/config/IOS.cmake)

    if (NOT EXISTS ${BOOST_IOS_ROOT})
        # See here for building boost: https://github.com/faithfracture/Apple-Boost-BuildScript.git
        message(FATAL_ERROR "BOOST_IOS_FRAMEWORK_ROOT_PATH not does not exist! Current path: ${BOOST_IOS_ROOT}")
    endif()

elseif(APPLE)
    message(STATUS "--- Build for Mac ---")
    set(CMAKE_PREFIX_PATH       ${CMAKE_PREFIX_PATH} "${QT_ROOT_PATH}/clang_64")
    set(CMAKE_MODULE_PATH       ${CMAKE_MODULE_PATH} "${QT_ROOT_PATH}/clang_64/lib/cmake/Qt5")

    set(CMAKE_OSX_ARCHITECTURES x86_64)

elseif(WIN32)
    message(STATUS "--- Build for Windows ---")
    set(CMAKE_PREFIX_PATH       ${CMAKE_PREFIX_PATH} "${QT_ROOT_PATH}/clang_64")
    set(CMAKE_MODULE_PATH       ${CMAKE_MODULE_PATH} "${QT_ROOT_PATH}/clang_64/lib/cmake/Qt5")

    # expand 32-bit app's address space to 3/4GB on 32/64-bit OS
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE" )

endif()

#-------------------------------------------------------------------------------

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    option(NI_COLOR_DIAGNOSTICS "Print compiler diagnostics in color" ON)
endif()

#-------------------------------------------------------------------------------

function(set_bundle_key Target Key Id)
    add_custom_command(TARGET ${Target} POST_BUILD
        COMMAND /usr/libexec/PlistBuddy -c "Set :${Key}  ${Id}" $<TARGET_FILE_DIR:${Target}>/../Info.plist
        )
endfunction()

#-------------------------------------------------------------------------------
