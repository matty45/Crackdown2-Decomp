#ifndef VFX_cReflectionMesh_H
#define VFX_cReflectionMesh_H

#include "rws/attributes.h"

namespace VFX
{
    class cReflectionMesh : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
