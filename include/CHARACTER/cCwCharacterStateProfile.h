#ifndef CHARACTER_cCwCharacterStateProfile_H
#define CHARACTER_cCwCharacterStateProfile_H

#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    // Base cNonGameBase (RuffKing); CD2's HandleEvents (0x82540900) runs on its CEventHandler subobject at 0x18.
    // Size 0xCC from its class-factory registrar.
    class cCwCharacterStateProfile : public cNonGameBase
    {
    public:
        // CD2 0x82540550: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual const char *RetCharacterStates() const;
        // CD2 0x82540900: CEventHandler slot 5 (this is the subobject at 0x18). RuffKing names the override and the
        // event.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        unsigned char m_unmodelled7C[0xC4 - 0x7C];
        RWS::CEventId m_Msg_Return_Self;            // 0xC4 (RuffKing 0xF4)

        CD2_LAYOUT_CHECKS(cCwCharacterStateProfile,
            CD2_SIZE(cCwCharacterStateProfile, 0xCC)
            CD2_OFFSET(cCwCharacterStateProfile, m_Msg_Return_Self, 0xC4))
    };
}

#endif
