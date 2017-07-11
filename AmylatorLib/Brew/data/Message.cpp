#include "Message.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <sstream>
#include <iostream>


namespace brew {namespace data {

//-----------------------------------------------------------------------------
    
Message::Message()
{}

//-----------------------------------------------------------------------------

void Message::addMashLog(const MashLog& log)
{
    _mashLogs.push_back( log );
}

void Message::addMashLog(float temp,bool relay, clock::Timestamp ts, int idx)
{
    addMashLog( MashLog(temp, relay, ts, idx) );
}

//-----------------------------------------------------------------------------

void Message::addMashRequest(const MashRequest request)
{
    _mashRequests.push_back( request );
}

void Message::addMashRequest(const MashRequest::RequestType type)
{
    addMashRequest( MashRequest(type) );
}


//-----------------------------------------------------------------------------
//--- Serialization
//-----------------------------------------------------------------------------

void Message::importAsString(std::string strData)
{
    try {
        std::istringstream archive_stream(strData);
        boost::archive::text_iarchive archive(archive_stream);
        archive >> *this;
    }
    catch(...) {
        std::cout << "Error: import message failed: " << strData << std::endl;
    }
}

//-----------------------------------------------------------------------------

auto Message::exportToString() -> std::string
{
    try {
        std::ostringstream ostream;
        boost::archive::text_oarchive archive(ostream);
        archive << *this ;
        return ostream.str();
    }
    catch(...) {
        std::cout << "Error: export message failed" << std::endl;
    }
    return std::string();
}

//------------------------------------------------------------------------------

}}

