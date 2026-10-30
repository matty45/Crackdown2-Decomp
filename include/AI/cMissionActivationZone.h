#ifndef AI_cMissionActivationZone_H
#define AI_cMissionActivationZone_H

#include "rws/attributes.h"

namespace AI
{
    class cMissionActivationZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
