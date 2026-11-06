// STAND-IN: RuffKing's base and member order, confirmed by CD2 constructor
// 0x8283E2F8 calling cGameModePrototype (0x8283B2B8). Table 0x8215B308 adds no slots.
#ifndef GAMEMANAGEMENT_CPVPGAMEMODEPROTOTYPE_H
#define GAMEMANAGEMENT_CPVPGAMEMODEPROTOTYPE_H
#include "GameManagement/cGameModePrototype.h"
namespace CHARACTER { class cGameDamageProfile; }
namespace GameManagement
{
    class cPvPGameModePrototype : public cGameModePrototype
    {
    public:
        cPvPGameModePrototype();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // RuffKing declares this getter inline; CD2's table folds its copy to 0x824513B8.
        virtual unsigned int RetDefaultEndLimit() { return m_aDefaultEndLimit; }
        virtual unsigned int RetDefaultTimeLimit();
        virtual unsigned int RetEndLimit(unsigned int index) const;
        virtual unsigned int RetTimeLimit(unsigned int index) const;
        virtual float RetSpawnPointTimeOut() const;
    protected:
        CHARACTER::cGameDamageProfile *m_pGameDamageProfile;
        unsigned int m_aDefaultEndLimit;
        unsigned int m_aDefaultTimeLimit;
        unsigned int m_aEndLimits[6];
        unsigned int m_aTimeLimits[6];
        unsigned int m_nNumOrbsForKill;
        float m_fKillSkillPointsModifier;
        float m_fDeathSkillPointsModifier;
        float m_fSpawnPointTimeOut;
        CD2_LAYOUT_CHECKS(cPvPGameModePrototype,
            CD2_SIZE(cPvPGameModePrototype, 0x148)
            CD2_OFFSET(cPvPGameModePrototype, m_pGameDamageProfile, 0xF8)
            CD2_OFFSET(cPvPGameModePrototype, m_aEndLimits, 0x104)
            CD2_OFFSET(cPvPGameModePrototype, m_aTimeLimits, 0x11C)
            CD2_OFFSET(cPvPGameModePrototype, m_nNumOrbsForKill, 0x134)
            CD2_OFFSET(cPvPGameModePrototype, m_fSpawnPointTimeOut, 0x140))
    };
}
#endif
