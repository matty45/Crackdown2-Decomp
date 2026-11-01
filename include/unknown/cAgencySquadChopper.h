#include "rws/attributes.h"
// unknown::cAgencySquadChopper (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826EDBC8) builds cClass(0x12066, "cAgencySquadChopper", 0x2360); 0x2360 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYSQUADCHOPPER_H
#define UNKNOWN_CAGENCYSQUADCHOPPER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencySquadChopper
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySquadChopperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAGENCYSQUADCHOPPER_H
