#ifndef AI_cMissionActivationCylinder_H
#define AI_cMissionActivationCylinder_H

#include "rws/attributes.h"

namespace AI
{
    class cMissionActivationCylinder : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
