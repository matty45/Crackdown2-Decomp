#ifndef Equip_cWeaponProjectile_H
#define Equip_cWeaponProjectile_H

#include "rws/attributes.h"

namespace Equip
{
    class cWeaponProjectile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
