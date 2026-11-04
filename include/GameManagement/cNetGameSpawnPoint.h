#include "cd2/layout.h"
#include "rws/attributes.h"
#ifndef GameManagement_cNetGameSpawnPoint_H
#define GameManagement_cNetGameSpawnPoint_H

#include "GameManagement/cGameModeSpawnPoint.h"

namespace GameManagement
{
    // Base relationship from RuffKing's PDB; this stand-in models no additional fields yet.
    class cNetGameSpawnPoint : public cGameModeSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8284D908 (MakeNew calls it).
        cNetGameSpawnPoint();

    private:
        unsigned char m_unmodelled60[0x80 - 0x60];

        CD2_LAYOUT_CHECKS(cNetGameSpawnPoint, CD2_SIZE(cNetGameSpawnPoint, 0x80))

    };
}

#endif
