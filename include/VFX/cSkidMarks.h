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
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CSKIDMARKS_H
