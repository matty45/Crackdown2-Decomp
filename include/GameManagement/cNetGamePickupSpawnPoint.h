#ifndef GameManagement_cNetGamePickupSpawnPoint_H
#define GameManagement_cNetGamePickupSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cNetGamePickupSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
