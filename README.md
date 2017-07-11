# README #

## INTRO ##

In brewing, mashing is a process where the grain bill and water is mixed and heated. The mash must be paused at certain temperatures, which are defided by the recipe. When brewing at home, without professional equipment, this can be cumbersome and unprecise... but it can be automated.
Amylator is a Server/Client based application. The server is running on a device with GPIO pins (typically a Raspberry Pi). A immersion heater and a temperature sensor is connected to the GPIO pins. The Client is running on another device which must be in the same network. There, you can setup and start your mash receip. Of course, the temperature will also be shown in a graph :)

## DETAILS ##

I will add a detailed description of the hardware and software in a blogpost soon. 

## BUILD ##

* cd *~/my/develop/dir*
* git clone --recursive https://Teuse@bitbucket.org/Teuse/brewpi.git
* mkdir build
* cd build
* cmake ../brewpi
* make

__Note__:
* Qt is expected to be at path "/Applications/Qt/5.7". To customize this path, set the cmake-variable **QT_ROOT_PATH** to the correct path. Example: cmake ../amylator/ -DQT_ROOT_PATH="/MyQtPath/blub/5.7"
* The application is designed to be cross platform. Nevertheless, it's just tested on mac and linux for now.

## Requirements ##

* boost
* Qt
* Portaudio
