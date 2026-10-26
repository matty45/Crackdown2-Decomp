#ifndef GameManagement_cWeaponPickupSpawnPoint_H
#define GameManagement_cWeaponPickupSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cWeaponPickupSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
