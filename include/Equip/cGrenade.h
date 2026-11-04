#include "rws/attributes.h"
// Equip::cGrenade (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FCFF38) registers "cGrenade" with MakeNew (0x8261DF40) and size 0x9C0.
#ifndef EQUIP_CGRENADE_H
#define EQUIP_CGRENADE_H

namespace Equip
{
    class cGrenade
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // EQUIP_CGRENADE_H
