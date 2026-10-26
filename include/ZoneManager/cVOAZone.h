#ifndef ZoneManager_cVOAZone_H
#define ZoneManager_cVOAZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cVOAZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
