#include "rws/attributes.h"
// Equip::cClusterGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82619888) builds cClass(0x3E8E, "cClusterGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CCLUSTERGRENADE_H
#define EQUIP_CCLUSTERGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cClusterGrenade
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcClusterGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCLUSTERGRENADE_H
