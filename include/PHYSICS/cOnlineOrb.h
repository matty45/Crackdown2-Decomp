#ifndef PHYSICS_cOnlineOrb_H
#define PHYSICS_cOnlineOrb_H

#include "rws/attributes.h"

namespace PHYSICS
{
    class cOnlineOrb : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
