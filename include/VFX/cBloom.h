#include "fun_runtime/class.h"
#include "rws/attributes.h"
// VFX::cBloom (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header; RetClassName
// (0x82791958) is slot 11 of the vtable at 0x8214C650, as cNonGameBase's RetClassName.
#ifndef VFX_CBLOOM_H
#define VFX_CBLOOM_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cBloom : public cNonGameBase
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x838f6280; its initializer names cBloom.
        static const Fun_Runtime::cClass *ms_pccBloomClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CBLOOM_H
