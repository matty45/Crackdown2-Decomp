#include "rws/attributes.h"
// Equip::cMiniGun (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8263B320) builds cClass(0x13268, "cMiniGun", 0xAC0); 0xAC0 is the size its registrar gives.
#ifndef EQUIP_CMINIGUN_H
#define EQUIP_CMINIGUN_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cMiniGun
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMiniGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CMINIGUN_H
