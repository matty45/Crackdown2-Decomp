#include "gom/object_prototype.h"
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
        // CD2 0x826165A8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCE608 names placement factory 0x826165b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcChainGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCHAINGUN_H
