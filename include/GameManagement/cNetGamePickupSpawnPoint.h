#include "rws/attributes.h"
#ifndef GameManagement_cNetGamePickupSpawnPoint_H
#define GameManagement_cNetGamePickupSpawnPoint_H

#include "GameManagement/cNetGameSpawnPoint.h"

namespace GameManagement
{
    // Base relationship from RuffKing's PDB; this stand-in models no additional fields yet.
    class cNetGamePickupSpawnPoint : public cNetGameSpawnPoint
    {
    public:
        // CD2 0x8284BB98 calls the shared spawn-point constructor at 0x8284D908.
        cNetGamePickupSpawnPoint();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    private:
        unsigned char m_unmodelled80[0xA0 - 0x80];
        CD2_LAYOUT_CHECKS(cNetGamePickupSpawnPoint, CD2_SIZE(cNetGamePickupSpawnPoint, 0xA0))
    };
}

#endif
