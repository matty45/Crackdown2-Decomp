#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "rws/attributes.h"
// VFX::cSkidMarks (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827B7AD8) is slot 11 of the vtable at 0x82009148, as cNonGameBase's RetClassName.
#ifndef VFX_CSKIDMARKS_H
#define VFX_CSKIDMARKS_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cSkidMarks : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSkidMarksClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x827B7A20 / 0x827B7A30: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
    public:
        // Out of line: CD2 0x827B7BC8 (MakeNew calls it).
        cSkidMarks();

    private:
        unsigned char m_unmodelled7C[0x2CC - 0x7C];

        CD2_LAYOUT_CHECKS(cSkidMarks, CD2_SIZE(cSkidMarks, 0x2CC))

    };
}

#endif // VFX_CSKIDMARKS_H
