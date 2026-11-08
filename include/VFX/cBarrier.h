// VFX::cBarrier (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8278F0E8, from its registrars in CD2's
// initializer run); RuffKing declares the class in VFX/cBarrier.h and defines it in cBarrier.obj. No layout or virtuals
// are modelled yet.
#ifndef VFX_CBARRIER_H
#define VFX_CBARRIER_H

#include "rws/attributes.h"

namespace VFX
{
    class cBarrier
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CBARRIER_H
