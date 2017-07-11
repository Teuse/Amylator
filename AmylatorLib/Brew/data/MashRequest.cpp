#include "MashRequest.h"


namespace brew { namespace data {

//-----------------------------------------------------------------------------
    
MashRequest::MashRequest()
: _type(TYPE_NONE)
{}

MashRequest::MashRequest(RequestType type) 
: _type(type)
{}

}}
