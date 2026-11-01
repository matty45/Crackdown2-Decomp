#ifndef unknown_cNetGamePickupGroupMemberSpawnPoint_H
#define unknown_cNetGamePickupGroupMemberSpawnPoint_H

#include "rws/attributes.h"

namespace unknown
{
    class cNetGamePickupGroupMemberSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
