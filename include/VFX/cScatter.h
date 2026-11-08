// VFX::cScatter (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827AA250, from its registrar in CD2's
// initializer run); RuffKing declares the class in VFX/cScatter.h and defines it in cScatter.obj, with
// cScatterMeshResources. No layout or virtuals are modelled yet.
#ifndef VFX_CSCATTER_H
#define VFX_CSCATTER_H

#include "rws/attributes.h"

namespace VFX
{
    class cScatter
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CSCATTER_H
