#include "cd2/layout.h"
#include "rws/attributes.h"
// VFX::cGlobalLightManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827FB028) is slot 11 of the vtable at 0x82155060, as cNonGameBase's RetClassName.
#ifndef VFX_CGLOBALLIGHTMANAGER_H
#define VFX_CGLOBALLIGHTMANAGER_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cGlobalLightManager : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcGlobalLightManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827FB998 (MakeNew calls it).
        cGlobalLightManager();

    private:
        unsigned char m_unmodelled7C[0x5AE0 - 0x7C];

        CD2_LAYOUT_CHECKS(cGlobalLightManager, CD2_SIZE(cGlobalLightManager, 0x5AE0))

    };
}

#endif // VFX_CGLOBALLIGHTMANAGER_H
