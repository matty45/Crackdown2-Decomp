#include "fun_runtime/class.h"
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
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x824E4390: the allocation factory calls this constructor out of line.
        cCharacterAnimSetManager();
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x838214ec; its initializer names cCharacterAnimSetManager.
        static const Fun_Runtime::cClass *ms_pcCharacterAnimSetManagerClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        unsigned char m_unmodelled7C[0x1400 - 0x7C];
        CD2_LAYOUT_CHECKS(cCharacterAnimSetManager, CD2_SIZE(cCharacterAnimSetManager, 0x1400))
    };
}

#endif // ANIM_CCHARACTERANIMSETMANAGER_H
