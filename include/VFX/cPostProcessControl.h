#ifndef VFX_cPostProcessControl_H
#define VFX_cPostProcessControl_H

#include "rws/attributes.h"

namespace VFX
{
    class cPostProcessControl : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
