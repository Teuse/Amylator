#include "MashStep.h"


namespace brew { namespace data {

//-----------------------------------------------------------------------------

MashStep::MashStep(float temp, clock::Duration dur)
: _temperature(temp)
, _duration(dur)
{ }

}}
