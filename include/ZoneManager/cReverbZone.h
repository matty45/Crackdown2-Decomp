#ifndef ZoneManager_cReverbZone_H
#define ZoneManager_cReverbZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cReverbZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
