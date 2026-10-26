#ifndef Vehicle_cEightWheelerProfile_H
#define Vehicle_cEightWheelerProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cEightWheelerProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
