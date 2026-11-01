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
        static const Fun_Runtime::cClass *ms_pcHWGrenadeProjectileClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // EQUIP_CHWGRENADEPROJECTILE_H
