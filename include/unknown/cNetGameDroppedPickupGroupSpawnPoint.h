#ifndef unknown_cNetGameDroppedPickupGroupSpawnPoint_H
#define unknown_cNetGameDroppedPickupGroupSpawnPoint_H

#include "rws/attributes.h"

namespace unknown
{
    class cNetGameDroppedPickupGroupSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
