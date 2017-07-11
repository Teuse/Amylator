#pragma once 
#include <string>
#include <chrono>


namespace brew { 

namespace clock 
{
    using Timestamp = std::chrono::system_clock::time_point;
    using Duration  = std::chrono::duration<float>;
}

namespace cfg
{
    const std::string serviceType = "_amylator._tcp";
    const unsigned short port     = 6780;
}


}

