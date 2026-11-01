// Equip::cCWFirearm (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82617DD0) builds cClass(0x3E81, "cCWFirearm", 0xAB0); 0xAB0 is the size its registrar gives.
#ifndef EQUIP_CCWFIREARM_H
#define EQUIP_CCWFIREARM_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cCWFirearm
    {
    public:
        static const Fun_Runtime::cClass *ms_pcCWFirearmClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCWFIREARM_H
