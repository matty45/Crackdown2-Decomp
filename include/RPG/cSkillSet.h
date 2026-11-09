// RPG::cSkillSet: CD2 descriptor 0x827539D0 gives size 0x64; its inheritance registrar identifies cDebugPageHandler.
// Burn/RuffKing give the member names/order. Their debug base is 0x24, CD2's is 4, moving each own field down 0x20.
// CD2 callees 0x82365580 and 0x82753BA8 read the skill arrays at +8/+0xE, bonus arrays at +0x14/+0x2C and
// transform flag at +0x5C. Embedded in cCwTransCharacter at +0x2CC4, the flag is +0x2D20 (getter 0x82538170).
#ifndef RPG_CSKILLSET_H
#define RPG_CSKILLSET_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"
#include "RPG/eSkills.h"

namespace CHARACTER { class cCwTransCharacter; }

namespace RPG
{
    class cSkillSet : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSkillSetClass;
        cSkillSet(CHARACTER::cCwTransCharacter *);
        virtual ~cSkillSet();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        bool IsTransformRequired() const { return m_bTransformRequired; }
        bool IsSkillAndBonusMaxed(int skill) const; // CD2 0x82753BA8
        bool IsSkillMaxed(int skill) const; // CD2 0x82365580

    private:
        CHARACTER::cCwTransCharacter *m_pOwner;
        char m_aPostTransfromSkills[eSk_Num]; // reference spelling
        char m_aSkills[eSk_Num];
        float m_aSkillBonus[eSk_Num];
        float m_aSkillTmpBonus[eSk_Num];
        float m_afUnsavedSkill[eSk_Num];
        bool m_bTransformRequired;
        bool m_bSquadSkillActive;
        unsigned char m_nNumActiveSquadSkillPlayers;
        unsigned char m_nCombinedSquadSkill;
        float m_fSquadSkillDeactivationTimer;

        CD2_LAYOUT_CHECKS(cSkillSet,
            CD2_SIZE(cSkillSet, 0x64)
            CD2_OFFSET(cSkillSet, m_pOwner, 4)
            CD2_OFFSET(cSkillSet, m_aPostTransfromSkills, 8)
            CD2_OFFSET(cSkillSet, m_aSkills, 0xE)
            CD2_OFFSET(cSkillSet, m_aSkillBonus, 0x14)
            CD2_OFFSET(cSkillSet, m_aSkillTmpBonus, 0x2C)
            CD2_OFFSET(cSkillSet, m_afUnsavedSkill, 0x44)
            CD2_OFFSET(cSkillSet, m_bTransformRequired, 0x5C)
            CD2_OFFSET(cSkillSet, m_bSquadSkillActive, 0x5D)
            CD2_OFFSET(cSkillSet, m_nNumActiveSquadSkillPlayers, 0x5E)
            CD2_OFFSET(cSkillSet, m_nCombinedSquadSkill, 0x5F)
            CD2_OFFSET(cSkillSet, m_fSquadSkillDeactivationTimer, 0x60))
    };
}

#endif // RPG_CSKILLSET_H
