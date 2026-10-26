#ifndef ZoneManager_cReverbZone_H
#define ZoneManager_cReverbZone_H

#include "rws/attributes.h"

namespace ZoneManager
{
    class cReverbZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
