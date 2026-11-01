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
    };
}

#endif // ANIM_CCHARACTERANIMSETMANAGER_H
