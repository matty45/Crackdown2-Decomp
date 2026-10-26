#ifndef GameManagement_cNetGamePlayerSpawnPoint_H
#define GameManagement_cNetGamePlayerSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cNetGamePlayerSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
