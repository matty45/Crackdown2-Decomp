// VFX::cBarrier (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8278F0E8, from its registrars in CD2's
// initializer run); RuffKing declares the class in VFX/cBarrier.h and defines it in cBarrier.obj. No layout or virtuals
// are modelled yet.
#ifndef VFX_CBARRIER_H
#define VFX_CBARRIER_H

#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace VFX
{
    // Burn's base order agrees with CD2 constructor 0x8278F850: debug-page
    // subobject at +0x18. Instance storage is not modelled.
    class cBarrier : public RWS::CAttributeHandler, public GDb::cDebugPageHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x8214C584, slot 11.
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CBARRIER_H
