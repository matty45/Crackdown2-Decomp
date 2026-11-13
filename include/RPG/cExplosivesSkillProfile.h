#include "fun_runtime/class.h"
#include "rws/attributes.h"
// RPG::cExplosivesSkillProfile: base and member names from RuffKing. CD2 factory
// 0x827530D0 establishes the shared 0x7C base, string at 0x7C, event at 0x98
// and absorbed-explosion percentage at 0xA0 (complete size 0xA4).
// Namespace from RuffKing's RPG/cExplosivesSkillProfile.h (base cNonGameBase there; CD2's inheritance registrar 0x82FFD3A0 agrees).
// Burn has it in CHARACTER without the cNonGameBase base, so CD2 follows RuffKing's version.
// Its class-factory registrar (0x82FFD408) registers "cExplosivesSkillProfile" with MakeNew (0x827530D0) and size 0xA4.
#ifndef RPG_CEXPLOSIVESSKILLPROFILE_H
#define RPG_CEXPLOSIVESSKILLPROFILE_H

#include "gom/non_game_base.h"
#include "fun_runtime/string.h"
#include "rws/eventid.h"

namespace RPG
{
    class cExplosivesSkillProfile : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosivesSkillProfileClass;
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cExplosivesSkillProfile();
        cExplosivesSkillProfile(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Term();
        // RuffKing declares this inline; CD2 primary slot 9 shares the true-return stub.
        virtual bool HandleDataInNewDesignBuild() { return true; }
        // CD2 event-handler table 0x82145B08 slot 5 holds 0x827533F8.
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        enum LoadParameterTypes
        {
            CMD_Msg_Return_Self = 0,
            CMD_AbsorbedExplosiveDamage = 1
        };
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    protected:
        Fun_Runtime::cString m_sProfileName;
        RWS::CEventId m_Msg_Return_Self;
        float m_fAbsorbedExplosionPercent;

        CD2_LAYOUT_CHECKS(cExplosivesSkillProfile,
            CD2_SIZE(cExplosivesSkillProfile, 0xA4)
            CD2_OFFSET(cExplosivesSkillProfile, m_sProfileName, 0x7C)
            CD2_OFFSET(cExplosivesSkillProfile, m_Msg_Return_Self, 0x98)
            CD2_OFFSET(cExplosivesSkillProfile, m_fAbsorbedExplosionPercent, 0xA0))
    };
}

#endif // RPG_CEXPLOSIVESSKILLPROFILE_H
