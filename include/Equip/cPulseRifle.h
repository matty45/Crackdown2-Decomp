#include "rws/attributes.h"
// Equip::cPulseRifle (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8260FAA0) builds cClass(0x27413, "cPulseRifle", 0xA80); 0xA80 is the size its registrar gives.
#ifndef EQUIP_CPULSERIFLE_H
#define EQUIP_CPULSERIFLE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cPulseRifle
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPulseRifleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPULSERIFLE_H
