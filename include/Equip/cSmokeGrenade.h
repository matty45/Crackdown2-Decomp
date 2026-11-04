#include "rws/attributes.h"
// Equip::cSmokeGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82622790) builds cClass(0x3E8D, "cSmokeGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CSMOKEGRENADE_H
#define EQUIP_CSMOKEGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cSmokeGrenade
    {
    public:
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSmokeGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CSMOKEGRENADE_H
