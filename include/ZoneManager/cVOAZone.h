#ifndef ZoneManager_cVOAZone_H
#define ZoneManager_cVOAZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cVOAZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
