#ifndef AI_cMissionCompletionZone_H
#define AI_cMissionCompletionZone_H

#include "rws/attributes.h"

namespace AI
{
    class cMissionCompletionZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
