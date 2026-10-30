#ifndef AI_cAmbientWanderAttackBehaviour_H
#define AI_cAmbientWanderAttackBehaviour_H

#include "rws/attributes.h"

namespace AI
{
    class cAmbientWanderAttackBehaviour : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
