#pragma once
#include <Brew/Config.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/binary_object.hpp>


namespace brew { namespace data {

//-----------------------------------------------------------------------------

class MashStep 
{
public:

    MashStep() {}
    MashStep(float temp, clock::Duration dur);

    auto temperature() const -> float { return _temperature; }
    void setTemperature(float temp)   { _temperature = temp; }

    auto duration() const -> clock::Duration { return _duration; }
    void setDuration(clock::Duration dur)    { _duration = dur; }
 
private:

    float           _temperature;
    clock::Duration _duration;

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, unsigned)
    {
        ar & _temperature;
        ar & boost::serialization::make_binary_object(&_duration, sizeof(_duration));
    }
};


}}

