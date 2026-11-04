#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Equip::cCWHeavyWeapon (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FD2F58) registers "cCWHeavyWeapon" with MakeNew (0x8262FC20) and size 0xA20.
#ifndef EQUIP_CCWHEAVYWEAPON_H
#define EQUIP_CCWHEAVYWEAPON_H

namespace Equip
{
    class cCWHeavyWeapon
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // EQUIP_CCWHEAVYWEAPON_H
