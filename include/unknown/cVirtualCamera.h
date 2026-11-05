#include "rws/attributes.h"
// unknown::cVirtualCamera: interface stand-in. CD2 constructor 0x8230C710 calls
// cGameBase and constructs cDebugPageHandler at +0x120; inheritance registrars
// identify both bases. Its descriptor and MakeNew allocation establish size 0xF10;
// unrecovered instance fields remain opaque.
// StaticCreateClass (0x8252CE88) builds cClass(0x637, "cVirtualCamera", 0xF10); 0xF10 is the size its registrar gives.
#ifndef UNKNOWN_CVIRTUALCAMERA_H
#define UNKNOWN_CVIRTUALCAMERA_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "GDb/cDebugPageHandler.h"

namespace unknown
{
    class cVirtualCamera : public cGameBase, public GDb::cDebugPageHandler
    {
    public:
        cVirtualCamera(); // CD2 0x8230C710, out of line
        // CD2 0x8252CDD0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8252CDC0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcVirtualCameraClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled124[0xF10 - 0x124];
        CD2_LAYOUT_CHECKS(cVirtualCamera, CD2_SIZE(cVirtualCamera, 0xF10))
    };
}

#endif // UNKNOWN_CVIRTUALCAMERA_H
