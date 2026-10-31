#ifndef GameManagement_cNetGameSpawnPoint_H
#define GameManagement_cNetGameSpawnPoint_H

#include "GameManagement/cGameModeSpawnPoint.h"

namespace GameManagement
{
    // Base relationship from RuffKing's PDB; this stand-in models no additional fields yet.
    class cNetGameSpawnPoint : public cGameModeSpawnPoint
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
