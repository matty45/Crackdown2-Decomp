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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
