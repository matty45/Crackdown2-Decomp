// Equip::cWeapon (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x822E5B60 (names the class "cWeapon"); derived classes register it as their parent. Name and namespace: RuffKing Equipment/Weapon/cWeapon.h.
#ifndef EQUIP_CWEAPON_H
#define EQUIP_CWEAPON_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cWeapon
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CWEAPON_H
