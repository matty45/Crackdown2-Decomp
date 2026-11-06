#include "cd2/layout.h"
#include "rws/attributes.h"
// CHARACTER::cGenCharProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x82556360) is slot 11 of the vtable at 0x82114298, as cNonGameBase's RetClassName.
#ifndef CHARACTER_CGENCHARPROFILE_H
#define CHARACTER_CGENCHARPROFILE_H

#include "gom/non_game_base.h"
#include "rws/eventid.h"

namespace CHARACTER
{
    class cGenCharProfile : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcGenCharProfileClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82243C58 (MakeNew calls it).
        cGenCharProfile();
        // CD2 0x82556458: CEventHandler slot 5 (this is the subobject at 0x18). RuffKing names the override and the
        // event.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        RWS::CEventId m_Msg_Return_Self;            // 0x7C

        CD2_LAYOUT_CHECKS(cGenCharProfile,
            CD2_SIZE(cGenCharProfile, 0x84)
            CD2_OFFSET(cGenCharProfile, m_Msg_Return_Self, 0x7C))

    };
}

#endif // CHARACTER_CGENCHARPROFILE_H
