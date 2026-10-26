#ifndef VFX_cScatterMeshResources_H
#define VFX_cScatterMeshResources_H

#include "rws/attributes.h"

namespace VFX
{
    class cScatterMeshResources : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
