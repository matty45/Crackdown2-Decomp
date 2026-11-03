#include "fun_runtime/class.h"
#ifndef Equip_cWeaponProjectile_H
#define Equip_cWeaponProjectile_H

#include "rws/attributes.h"

namespace Equip
{
    class cWeaponProjectile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x8260A7A0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
