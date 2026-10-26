#ifndef VFX_cDeityRay_H
#define VFX_cDeityRay_H

#include "rws/attributes.h"

namespace VFX
{
    class cDeityRay : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
