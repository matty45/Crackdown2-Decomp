#ifndef VFX_cScatterMeshResources_H
#define VFX_cScatterMeshResources_H

#include "rws/attributes.h"

namespace VFX
{
    class cScatterMeshResources : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
