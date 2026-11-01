#include "rws/attributes.h"
// Equip::cProxMine (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8261F960) builds cClass(0x13265, "cProxMine", 0xB10); 0xB10 is the size its registrar gives.
#ifndef EQUIP_CPROXMINE_H
#define EQUIP_CPROXMINE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cProxMine
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcProxMineClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPROXMINE_H
