#include "rws/attributes.h"
// Equip::cHarpoonBolt (Crackdown 2): STAND-IN for the class name only. Base Equip::cWeaponProjectile, as in RuffKing's
// header; RetClassName (0x826271D8) is slot 11 of the vtable at 0x82010B60, as cNonGameBase's RetClassName.
#ifndef EQUIP_CHARPOONBOLT_H
#define EQUIP_CHARPOONBOLT_H

#include "Equip/cWeaponProjectile.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"

namespace Equip
{
    class cHarpoonBolt : public Equip::cWeaponProjectile
    {
    public:
        // Name and base from RuffKing. CD2's MakeNew (0x82627168) allocates 0x2F0, calls cEquipmentPrototype's
        // constructor (0x826071F8) and stores this class's vptrs: both derived constructors are inline and add no
        // fields.
        class cHarpoonBoltPrototype : public cWeaponProjectile::cWeaponProjectilePrototype
        {
        public:
            __forceinline cHarpoonBoltPrototype(const RWS::CAttributePacket &packet)
                : cWeaponProjectile::cWeaponProjectilePrototype(packet) {}

            CD2_LAYOUT_CHECKS(cHarpoonBoltPrototype,
                CD2_SIZE(cHarpoonBoltPrototype, 0x2F0))
        };

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cHarpoonBolt();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcHarpoonBoltClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // EQUIP_CHARPOONBOLT_H
