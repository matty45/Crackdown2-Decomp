#include "cd2/layout.h"
#include "rws/attributes.h"
// VFX::cProjectedDecal (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827A5688) is slot 11 of the vtable at 0x820099E0, as cNonGameBase's RetClassName.
#ifndef VFX_CPROJECTEDDECAL_H
#define VFX_CPROJECTEDDECAL_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cProjectedDecal : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcProjectedDecalClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827A6678 (MakeNew calls it).
        cProjectedDecal();

    private:
        unsigned char m_unmodelled7C[0x28C - 0x7C];

        CD2_LAYOUT_CHECKS(cProjectedDecal, CD2_SIZE(cProjectedDecal, 0x28C))

    };
}

#endif // VFX_CPROJECTEDDECAL_H
