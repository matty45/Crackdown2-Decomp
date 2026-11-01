#ifndef GameManagement_cGameModeSpawnPoint_H
#define GameManagement_cGameModeSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cGameModeSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
