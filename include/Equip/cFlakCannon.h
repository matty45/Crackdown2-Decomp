// Equip::cFlakCannon (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8263A850) builds cClass(0x13269, "cFlakCannon", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLAKCANNON_H
#define EQUIP_CFLAKCANNON_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlakCannon
    {
    public:
        static const Fun_Runtime::cClass *ms_pcFlakCannonClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CFLAKCANNON_H
