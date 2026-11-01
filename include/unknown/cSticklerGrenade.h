#include "rws/attributes.h"
// unknown::cSticklerGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82623330) builds cClass(0x10144, "cSticklerGrenade", 0x9E0); 0x9E0 is the size its registrar gives.
#ifndef UNKNOWN_CSTICKLERGRENADE_H
#define UNKNOWN_CSTICKLERGRENADE_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSticklerGrenade
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSticklerGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSTICKLERGRENADE_H
