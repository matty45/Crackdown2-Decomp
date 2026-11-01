#include "rws/attributes.h"
// Equip::cRealNadeLauncher (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82634B00) builds cClass(0x6067, "cRealNadeLauncher", 0xA20); 0xA20 is the size its registrar gives.
#ifndef EQUIP_CREALNADELAUNCHER_H
#define EQUIP_CREALNADELAUNCHER_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cRealNadeLauncher
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRealNadeLauncherClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CREALNADELAUNCHER_H
