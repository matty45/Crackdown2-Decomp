#include "cd2/layout.h"
#include "rws/attributes.h"
// VFX::cOutlines (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827A0BE0) is slot 11 of the vtable at 0x82008E18, as cNonGameBase's RetClassName.
#ifndef VFX_COUTLINES_H
#define VFX_COUTLINES_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cOutlines : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcOutlinesClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x821D5398 (MakeNew calls it).
        cOutlines();

    private:
        unsigned char m_unmodelled7C[0x460 - 0x7C];

        CD2_LAYOUT_CHECKS(cOutlines, CD2_SIZE(cOutlines, 0x460))

    };
}

#endif // VFX_COUTLINES_H
