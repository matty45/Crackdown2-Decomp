#ifndef CHARACTER_cAgentTintProfile_H
#define CHARACTER_cAgentTintProfile_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cAgentTintProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
