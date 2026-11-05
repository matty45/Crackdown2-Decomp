#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cHWGrenadeProjectile (Crackdown 2): STAND-IN for the class name only. Base Equip::cHWProjectile, as in
// RuffKing's header; RetClassName (0x82629390) is slot 11 of the vtable at 0x82127130, as cNonGameBase's RetClassName.
#ifndef EQUIP_CHWGRENADEPROJECTILE_H
#define EQUIP_CHWGRENADEPROJECTILE_H

#include "Equip/cFlocket.h"

namespace Equip
{
    class cHWGrenadeProjectile : public Equip::cHWProjectile
    {
    public:
        // CD2 0x826293C0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 spawning initializer 0x82FD2320 names placement factory 0x826293a0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcHWGrenadeProjectileClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // EQUIP_CHWGRENADEPROJECTILE_H
