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
    };
}

#endif
