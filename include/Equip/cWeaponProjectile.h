#include "gom/object_prototype.h"
#include "fun_runtime/class.h"
// Base cEquipment: CD2's constructor 0x82609610 calls cEquipment's (0x82604AF8) and the destructor 0x826096C0 calls
// cEquipment's (0x82604CA8); both only restore this class's vtables. Derived storage is not modelled.
#ifndef Equip_cWeaponProjectile_H
#define Equip_cWeaponProjectile_H

#include "Equip/cEquipment.h"

#include "rws/attributes.h"

namespace Equip
{
    class cWeaponProjectile : public cEquipment
    {
    public:
        // CD2 factory 0x826095F8 forwards only this, without a prototype argument.
        cWeaponProjectile();
        // CD2 0x826096C0.
        virtual ~cWeaponProjectile();
        // CD2 spawning initializer 0x82FCBFB8 names placement factory 0x826095f8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8260A7A0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
