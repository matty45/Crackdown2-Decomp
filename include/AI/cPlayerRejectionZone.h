#include "rws/attributes.h"
// AI::cPlayerRejectionZone (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82F8FD58) registers "cPlayerRejectionZone" with MakeNew (0x8248B898) and size 0x100.
#ifndef AI_CPLAYERREJECTIONZONE_H
#define AI_CPLAYERREJECTIONZONE_H

namespace AI
{
    class cPlayerRejectionZone
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CPLAYERREJECTIONZONE_H
