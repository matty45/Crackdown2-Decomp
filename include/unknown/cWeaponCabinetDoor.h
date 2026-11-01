// unknown::cWeaponCabinetDoor (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82741100) builds cClass(0x1021, "cWeaponCabinetDoor", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONCABINETDOOR_H
#define UNKNOWN_CWEAPONCABINETDOOR_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponCabinetDoor
    {
    public:
        static const Fun_Runtime::cClass *ms_pcWeaponCabinetDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CWEAPONCABINETDOOR_H
