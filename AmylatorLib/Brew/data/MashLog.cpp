#include "MashLog.h"


namespace brew { namespace data {

//-----------------------------------------------------------------------------
    
MashLog::MashLog()
{ }
        
MashLog::MashLog(float temp, bool relay, clock::Timestamp ts, int idx)
: _timestamp(ts)
, _temparature(temp)
, _relayState(relay)
, _stepIndex(idx)
{ }

}}
