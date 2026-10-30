#ifndef AI_PedestrianGuard_H
#define AI_PedestrianGuard_H

#include "rws/attributes.h"

namespace AI
{
    class PedestrianGuard : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
