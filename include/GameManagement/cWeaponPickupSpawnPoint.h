#ifndef GameManagement_cWeaponPickupSpawnPoint_H
#define GameManagement_cWeaponPickupSpawnPoint_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cWeaponPickupSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8284C630 (MakeNew calls it with the packet).
        cWeaponPickupSpawnPoint(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0xD0 - 0x18];

        CD2_LAYOUT_CHECKS(cWeaponPickupSpawnPoint, CD2_SIZE(cWeaponPickupSpawnPoint, 0xD0))

    };
}

#endif
