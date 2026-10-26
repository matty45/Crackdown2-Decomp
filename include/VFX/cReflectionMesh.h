#ifndef VFX_cReflectionMesh_H
#define VFX_cReflectionMesh_H

#include "rws/attributes.h"

namespace VFX
{
    class cReflectionMesh : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
