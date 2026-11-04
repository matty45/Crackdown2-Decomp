#include "cd2/layout.h"
#include "rws/attributes.h"
// Anim::cCharacterAnimSetManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x824E4380) is slot 11 of the vtable at 0x8210FA40, as cNonGameBase's RetClassName.
#ifndef ANIM_CCHARACTERANIMSETMANAGER_H
#define ANIM_CCHARACTERANIMSETMANAGER_H

#include "gom/non_game_base.h"

namespace Anim
{
    class cCharacterAnimSetManager : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x824E4390 (MakeNew calls it).
        cCharacterAnimSetManager();

    private:
        unsigned char m_unmodelled7C[0x1400 - 0x7C];

        CD2_LAYOUT_CHECKS(cCharacterAnimSetManager, CD2_SIZE(cCharacterAnimSetManager, 0x1400))

    };
}

#endif // ANIM_CCHARACTERANIMSETMANAGER_H
