// Equip::cCWWeapon (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82607C30) builds cClass(0x3E82, "cCWWeapon", 0xA10); 0xA10 is the size its registrar gives.
#ifndef EQUIP_CCWWEAPON_H
#define EQUIP_CCWWEAPON_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cCWWeapon
    {
    public:
        static const Fun_Runtime::cClass *ms_pcCWWeaponClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCWWEAPON_H
