#ifndef ZoneManager_cAmbienceZone_H
#define ZoneManager_cAmbienceZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cAmbienceZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
