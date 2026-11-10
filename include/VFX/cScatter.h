// VFX::cScatter (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827AA250, from its registrar in CD2's
// initializer run); RuffKing declares the class in VFX/cScatter.h and defines it in cScatter.obj, with
// cScatterMeshResources. No layout or virtuals are modelled yet.
#ifndef VFX_CSCATTER_H
#define VFX_CSCATTER_H

#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace VFX
{
    // Burn's base order agrees with CD2 constructor 0x827AB490: debug-page
    // subobject at +0x18. Instance storage is not modelled.
    class cScatter : public RWS::CAttributeHandler, public GDb::cDebugPageHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x8214E414, slot 11.
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CSCATTER_H
