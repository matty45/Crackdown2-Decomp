#ifndef CHARACTER_cGameDamageProfile_H
#define CHARACTER_cGameDamageProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cGameDamageProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
