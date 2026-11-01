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
        static const Fun_Runtime::cClass *ms_pcOutlinesClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_COUTLINES_H
