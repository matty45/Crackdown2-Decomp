#ifndef VFX_cLinkedVFXPrototype_H
#define VFX_cLinkedVFXPrototype_H

#include "rws/attributes.h"

namespace VFX
{
    class cLinkedVFXPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
