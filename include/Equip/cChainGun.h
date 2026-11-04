#include "rws/attributes.h"
// Equip::cChainGun (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82616690) builds cClass(0x13266, "cChainGun", 0xAC0); 0xAC0 is the size its registrar gives.
#ifndef EQUIP_CCHAINGUN_H
#define EQUIP_CCHAINGUN_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cChainGun
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcChainGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCHAINGUN_H
