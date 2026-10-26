#ifndef AI_cMissionActivationZone_H
#define AI_cMissionActivationZone_H

#include "rws/attributes.h"

namespace AI
{
    class cMissionActivationZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
