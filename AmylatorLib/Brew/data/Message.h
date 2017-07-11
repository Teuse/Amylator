#pragma once
#include <Brew/data/MashStep.h>
#include <Brew/data/MashRequest.h>
#include <Brew/data/MashLog.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <vector>


namespace brew { namespace data {

//-----------------------------------------------------------------------------

class Message
{
public:
    Message();

    auto hasMashLogs() const -> bool                   { return !_mashLogs.empty(); }
    auto mashLogs() const -> std::vector<MashLog>      { return _mashLogs; }
    void setMashLogs(const std::vector<MashLog>& logs) { _mashLogs = logs; }
    void addMashLog(const MashLog&);
    void addMashLog(float temp,bool relay, clock::Timestamp ts, int idx=-1);

    auto hasMashRequests() const -> bool                       { return !_mashRequests.empty(); }
    auto mashRequests() const -> std::vector<MashRequest>      { return _mashRequests; }
    void setMashRequests(const std::vector<MashRequest>& reqs) { _mashRequests = reqs; }
    void addMashRequest(const MashRequest request);
    void addMashRequest(const MashRequest::RequestType type);

    auto hasMashSteps() const -> bool                     { return !_mashSteps.empty(); }
    auto mashSteps() const -> std::vector<MashStep>       { return _mashSteps; }
    void setMashSteps(const std::vector<MashStep>& steps) { _mashSteps = steps; }

    // --- IMPORT & EXPORT
    void importAsString(std::string dataStr);
    auto exportToString() -> std::string;


private:

    std::vector<MashStep>    _mashSteps;
    std::vector<MashLog>     _mashLogs;
    std::vector<MashRequest> _mashRequests;


    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    friend class boost::serialization::access;
    template <typename Archive> 
    void serialize(Archive& ar, const unsigned int)
    {
        ar & _mashSteps;
        ar & _mashLogs;
        ar & _mashRequests;
    }
};

}}
