#ifndef VFX_cLightData_H
#define VFX_cLightData_H

#include "rws/attributes.h"

namespace VFX
{
    class cLightData : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
