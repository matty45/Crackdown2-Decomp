#ifndef ZoneManager_cAmbienceZone_H
#define ZoneManager_cAmbienceZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cAmbienceZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
