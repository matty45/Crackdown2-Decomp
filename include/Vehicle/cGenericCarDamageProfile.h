#ifndef Vehicle_cGenericCarDamageProfile_H
#define Vehicle_cGenericCarDamageProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cGenericCarDamageProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
