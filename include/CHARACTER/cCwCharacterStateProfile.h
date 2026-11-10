#ifndef CHARACTER_cCwCharacterStateProfile_H
#define CHARACTER_cCwCharacterStateProfile_H

#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/eventid.h"
#include "fun_runtime/string.h"
#include "cd2/layout.h"

namespace Anim
{
    class cAnimationProfile;
}

namespace CHARACTER
{
    // RuffKing's StateData (same header), 0x2C bytes; CD2's constructor (0x82540360) sets the eight non-patrol
    // speeds to 1.0 and the profile pointer to null.
    struct StateData
    {
        Anim::cAnimationProfile *m_pAnimationProfile;   // 0x0
        float m_fMinCrouchSpeed;                        // 0x4
        float m_fMaxCrouchSpeed;                        // 0x8
        float m_fMinWalkSpeed;                          // 0xC
        float m_fMaxWalkSpeed;                          // 0x10
        float m_fMinPatrolWalkSpeed;                    // 0x14
        float m_fMaxPatrolWalkSpeed;                    // 0x18
        float m_fMinRunSpeed;                           // 0x1C
        float m_fMaxRunSpeed;                           // 0x20
        float m_fMinSprintSpeed;                        // 0x24
        float m_fMaxSprintSpeed;                        // 0x28

        CD2_LAYOUT_CHECKS(StateData, CD2_SIZE(StateData, 0x2C))
    };

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
        // CD2 0x82540360 (default constructor) and 0x82540490 (destructor; deleting wrapper 0x82540440).
        cCwCharacterStateProfile();
        virtual ~cCwCharacterStateProfile();

    private:
        StateData m_StateData[1];                   // 0x7C (RuffKing 0xAC)
        Fun_Runtime::cString m_sProfileName;        // 0xA8 (RuffKing 0xD8)
        RWS::CEventId m_Msg_Return_Self;            // 0xC4 (RuffKing 0xF4)

        CD2_LAYOUT_CHECKS(cCwCharacterStateProfile,
            CD2_SIZE(cCwCharacterStateProfile, 0xCC)
            CD2_OFFSET(cCwCharacterStateProfile, m_StateData, 0x7C)
            CD2_OFFSET(cCwCharacterStateProfile, m_sProfileName, 0xA8)
            CD2_OFFSET(cCwCharacterStateProfile, m_Msg_Return_Self, 0xC4))
    };
}

#endif
