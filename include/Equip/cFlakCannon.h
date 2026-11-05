#include "Equip/cCWHeavyWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cFlakCannon (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWHeavyWeapon: the destructor 0x8263A940 calls cCWHeavyWeapon's (0x8262FCB0).
// StaticCreateClass (0x8263A850) builds cClass(0x13269, "cFlakCannon", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLAKCANNON_H
#define EQUIP_CFLAKCANNON_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlakCannon : public cCWHeavyWeapon
    {
    public:
        // CD2 0x8263A770: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8263A940.
        virtual ~cFlakCannon();
        // CD2 spawning initializer 0x82FD4368 names placement factory 0x8263a780.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFlakCannonClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CFLAKCANNON_H
