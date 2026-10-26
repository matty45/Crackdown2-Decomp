#ifndef VFX_cPostProcessEffectsControl_H
#define VFX_cPostProcessEffectsControl_H

#include "rws/attributes.h"

namespace VFX
{
    class cPostProcessEffectsControl : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
