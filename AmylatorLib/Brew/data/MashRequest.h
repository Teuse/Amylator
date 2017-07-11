#pragma once
#include <boost/serialization/access.hpp>


namespace brew { namespace data {

//-----------------------------------------------------------------------------

class MashRequest
{
public:
    enum RequestType
    {
        TYPE_NONE,
        TYPE_GET_LOG_FULL,

        TYPE_SET_LOG_UPDATE,
        TYPE_SET_LOG_FULL,
        TYPE_SET_START_MASH,
        TYPE_SET_STOP_MASH,
        TYPE_SET_PAUSE_MASH
    };

    MashRequest();
    MashRequest(RequestType type);

    RequestType type() const { return _type; }

private:

    RequestType _type;

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    friend class boost::serialization::access;
    template <typename Archive> 
    void serialize(Archive& ar, unsigned)
    {
        ar & _type;
    }
};

}}

