// unknown::cWeaponisedHelicopter (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826E19C8) builds cClass(0x4C70, "cWeaponisedHelicopter", 0x2DB0); 0x2DB0 is the size its registrar gives.
#ifndef UNKNOWN_CWEAPONISEDHELICOPTER_H
#define UNKNOWN_CWEAPONISEDHELICOPTER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cWeaponisedHelicopter
    {
    public:
        static const Fun_Runtime::cClass *ms_pcWeaponisedHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CWEAPONISEDHELICOPTER_H
