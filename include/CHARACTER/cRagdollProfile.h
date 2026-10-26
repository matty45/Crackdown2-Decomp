#ifndef CHARACTER_cRagdollProfile_H
#define CHARACTER_cRagdollProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cRagdollProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
