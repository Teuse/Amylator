#pragma once
#include <Brew/Config.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/binary_object.hpp>


namespace brew { namespace data {

//-----------------------------------------------------------------------------
    
class MashLog
{
public:

    MashLog();
    MashLog(float temp, bool relay, clock::Timestamp ts, int idx=-1);

    clock::Timestamp timestamp() const { return _timestamp;      }
    float temperature()          const { return _temparature;    }
    bool  relayState()           const { return _relayState;     }
    int   scheduleIndex()        const { return _stepIndex;      }
    bool  isProcessing()         const { return _stepIndex >= 0; }


private:

    clock::Timestamp _timestamp;
    float            _temparature = 0.f;
    bool             _relayState  = false;
    int              _stepIndex   = -1;

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, unsigned)
    {
        ar & boost::serialization::make_binary_object(&_timestamp, sizeof(_timestamp));
        ar & _temparature;
        ar & _relayState;
        ar & _stepIndex;
    }
};

}}

