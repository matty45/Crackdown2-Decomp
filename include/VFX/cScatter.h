// VFX::cScatter (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827AA250, from its registrar in CD2's
// initializer run); RuffKing declares the class in VFX/cScatter.h and defines it in cScatter.obj, with
// cScatterMeshResources. The base chain and complete size are recovered; own storage remains opaque.
#ifndef VFX_CSCATTER_H
#define VFX_CSCATTER_H

#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace VFX
{
    // Burn's base order agrees with CD2 constructor 0x827AB490: debug-page
    // subobject at +0x18. Instance storage is not modelled.
    __declspec(align(16)) class cScatter : public RWS::CAttributeHandler, public GDb::cDebugPageHandler
    {
    public:
        // CD2 0x827AB490: factory calls construction out of line without a packet.
        cScatter();
        virtual ~cScatter();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x8214E414, slot 11.
        virtual const char *RetClassName() const;
    private:
        // Reference renderer/SIMD storage; CD2 factory and registrar give the complete 0x550-byte size.
        unsigned char m_unmodelled1C[0x550 - 0x1C];
        CD2_LAYOUT_CHECKS(cScatter, CD2_SIZE(cScatter, 0x550))
    };
}

#endif // VFX_CSCATTER_H
