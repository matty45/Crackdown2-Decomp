#ifndef AI_cAmbientWanderAttackBehaviour_H
#define AI_cAmbientWanderAttackBehaviour_H

#include "rws/attributes.h"

namespace AI
{
    class cAmbientWanderAttackBehaviour : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
