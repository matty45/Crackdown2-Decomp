#ifndef Vehicle_cSixWheelerProfile_H
#define Vehicle_cSixWheelerProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cSixWheelerProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
