#ifndef AI_cBreachExplosion_H
#define AI_cBreachExplosion_H

#include "rws/attributes.h"

namespace AI
{
    class cBreachExplosion : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
