// VFX::cBarrierSettings (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8278EFA8, from its registrars in
// CD2's initializer run); RuffKing declares the class in VFX/cBarrier.h and defines it in cBarrier.obj. No layout or
// virtuals are modelled yet.
#ifndef VFX_CBARRIERSETTINGS_H
#define VFX_CBARRIERSETTINGS_H

#include "rws/attributes.h"

namespace VFX
{
    // Burn's base agrees with the five base-field clears in CD2 0x8278EFA8.
    // Instance fields remain unmodelled.
    class cBarrierSettings : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 table 0x8214C550, slot 11.
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CBARRIERSETTINGS_H
