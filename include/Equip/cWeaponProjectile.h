#ifndef Equip_cWeaponProjectile_H
#define Equip_cWeaponProjectile_H

#include "rws/attributes.h"

namespace Equip
{
    class cWeaponProjectile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
