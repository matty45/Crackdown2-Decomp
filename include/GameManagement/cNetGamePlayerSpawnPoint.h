#include "rws/attributes.h"
#ifndef GameManagement_cNetGamePlayerSpawnPoint_H
#define GameManagement_cNetGamePlayerSpawnPoint_H

#include "GameManagement/cNetGameSpawnPoint.h"

namespace GameManagement
{
    // Base relationship from RuffKing's PDB; this stand-in models no additional fields yet.
    class cNetGamePlayerSpawnPoint : public cNetGameSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
