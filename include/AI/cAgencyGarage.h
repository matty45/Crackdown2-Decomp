#include "rws/attributes.h"
// AI::cAgencyGarage (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82F8B1E8) registers "cAgencyGarage" with MakeNew (0x82479B80) and size 0x380.
#ifndef AI_CAGENCYGARAGE_H
#define AI_CAGENCYGARAGE_H

namespace AI
{
    class cAgencyGarage
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CAGENCYGARAGE_H
