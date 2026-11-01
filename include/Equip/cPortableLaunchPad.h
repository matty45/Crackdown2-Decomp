// Equip::cPortableLaunchPad (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8260DE78) builds cClass(0x27412, "cPortableLaunchPad", 0xCA0); 0xCA0 is the size its registrar gives.
#ifndef EQUIP_CPORTABLELAUNCHPAD_H
#define EQUIP_CPORTABLELAUNCHPAD_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cPortableLaunchPad
    {
    public:
        static const Fun_Runtime::cClass *ms_pcPortableLaunchPadClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPORTABLELAUNCHPAD_H
