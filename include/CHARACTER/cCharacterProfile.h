#ifndef CHARACTER_cCharacterProfile_H
#define CHARACTER_cCharacterProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/eventid.h"

namespace CHARACTER
{
    // Base cNonGameBase (RuffKing); CD2's HandleEvents (0x825552D8) runs on its CEventHandler subobject at 0x18.
    class cCharacterProfile : public cNonGameBase
    {
    public:
        // CD2 0x82553650: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x825531E8 (MakeNew calls it).
        cCharacterProfile();
        // CD2 0x825552D8: CEventHandler slot 5 (this is the subobject at 0x18). RuffKing names the override and the
        // event.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        unsigned char m_unmodelled7C[0x24C - 0x7C];
        RWS::CEventId m_Msg_Return_Self;            // 0x24C (RuffKing 0x27C)
        unsigned char m_unmodelled254[0x260 - 0x254];

        CD2_LAYOUT_CHECKS(cCharacterProfile,
            CD2_SIZE(cCharacterProfile, 0x260)
            CD2_OFFSET(cCharacterProfile, m_Msg_Return_Self, 0x24C))

    };
}

#endif
