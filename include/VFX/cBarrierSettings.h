// VFX::cBarrierSettings (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8278EFA8, from its registrars in
// CD2's initializer run); RuffKing declares the class in VFX/cBarrier.h and defines it in cBarrier.obj. No layout or
// virtuals are modelled yet.
#ifndef VFX_CBARRIERSETTINGS_H
#define VFX_CBARRIERSETTINGS_H

#include "rws/attributes.h"

namespace VFX
{
    class cBarrierSettings
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CBARRIERSETTINGS_H
