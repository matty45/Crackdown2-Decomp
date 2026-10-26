#ifndef Vehicle_cHelicopterDamageProfile_H
#define Vehicle_cHelicopterDamageProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cHelicopterDamageProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
