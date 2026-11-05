#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cMiniGun (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWFirearm: the destructor 0x8263B410 calls cCWFirearm's (0x82617EB8).
// StaticCreateClass (0x8263B320) builds cClass(0x13268, "cMiniGun", 0xAC0); 0xAC0 is the size its registrar gives.
#ifndef EQUIP_CMINIGUN_H
#define EQUIP_CMINIGUN_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cMiniGun : public cCWFirearm
    {
    public:
        // CD2 0x8263B240: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8263B410.
        virtual ~cMiniGun();
        // CD2 spawning initializer 0x82FD4718 names placement factory 0x8263b250.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMiniGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CMINIGUN_H
