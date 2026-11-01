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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cHarpoonBolt();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcHarpoonBoltClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // EQUIP_CHARPOONBOLT_H
