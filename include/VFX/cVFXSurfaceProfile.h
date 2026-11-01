// VFX::cVFXSurfaceProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827CCC50) is slot 11 of the vtable at 0x82150BA8, as cNonGameBase's RetClassName.
#ifndef VFX_CVFXSURFACEPROFILE_H
#define VFX_CVFXSURFACEPROFILE_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cVFXSurfaceProfile : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcVFXSurfaceProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CVFXSURFACEPROFILE_H
