#ifndef AI_cAITargetingProfile_H
#define AI_cAITargetingProfile_H

#include "rws/attributes.h"

namespace AI
{
    class cAITargetingProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
