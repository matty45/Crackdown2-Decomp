#ifndef GameManagement_cWeaponPickupSpawnPoint_H
#define GameManagement_cWeaponPickupSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cWeaponPickupSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
