#ifndef VFX_cSkyDome_H
#define VFX_cSkyDome_H

#include "rws/attributes.h"

namespace VFX
{
    class cSkyDome : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
