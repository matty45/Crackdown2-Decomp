// AI::cCharacterEntity (Crackdown 2): STAND-IN for the AI entity a character interface drives (cCharacterEntityIF's
// m_pAIEntity). Only fields that matched code reads; RuffKing's class (Kaim::CEntity base) gives the names. Evidence:
//   - m_name (0x4): Kaim::CEntity::m_name in RuffKing; CD2's cAiPlayer::RetName (0x823EB508) returns it, as RuffKing's
//     cAiPlayer::RetName does.
//   - CD2's cCharacterEntityIF registers script methods over these fields: "RetViewingAngle" (0x823EBFB8: 0x88),
//     "RetViewingDistance" (0x823EBFF8: 0x90), "RetThreatObjectViewingDistance" (0x823EC008: 0x98, CD2 only),
//     "RetHearingAcuteness" (0x823EC018: 0x9C), "RetHeadDirection" (0x823EBF98: address of 0xA0) and
//     "RetEyePosition" (0x823EBFA8: address of 0xB0). RuffKing has the same fields at 0x88, 0x90, 0xA0 and 0xB0.
//   - m_pOwner (0xC8; RuffKing 0xC4, CD2 has one more word before it): the owning cCharacterEntityIF; RetViewingAngle
//     reads its character pointer (+0x88).
#ifndef AI_CCHARACTERENTITY_H
#define AI_CCHARACTERENTITY_H

#include "fun_runtime/vec3.h"
#include "cd2/layout.h"

namespace AI
{
    class cCharacterEntityIF;

    class cCharacterEntity
    {
    private:
        unsigned char m_pad0[0x4];
    public:
        const char *m_name;                         // 0x4
    private:
        unsigned char m_pad8[0x88 - 0x8];
    public:
        float m_fViewingAngle;                      // 0x88
    private:
        unsigned char m_pad8C[0x90 - 0x8C];
    public:
        float m_fViewingDistance;                   // 0x90
    private:
        unsigned char m_pad94[0x98 - 0x94];
    public:
        float m_fThreatObjectViewingDistance;       // 0x98
        float m_fHearingAcuteness;                  // 0x9C
        Fun_Runtime::Vec3 m_vecHeadDirection;       // 0xA0
        Fun_Runtime::Vec3 m_vecEyePosition;         // 0xB0
    private:
        unsigned char m_padC0[0xC8 - 0xC0];
    public:
        cCharacterEntityIF *m_pOwner;               // 0xC8

        CD2_LAYOUT_CHECKS(cCharacterEntity,
            CD2_OFFSET(cCharacterEntity, m_name, 0x4)
            CD2_OFFSET(cCharacterEntity, m_fViewingAngle, 0x88)
            CD2_OFFSET(cCharacterEntity, m_fViewingDistance, 0x90)
            CD2_OFFSET(cCharacterEntity, m_fThreatObjectViewingDistance, 0x98)
            CD2_OFFSET(cCharacterEntity, m_fHearingAcuteness, 0x9C)
            CD2_OFFSET(cCharacterEntity, m_vecHeadDirection, 0xA0)
            CD2_OFFSET(cCharacterEntity, m_vecEyePosition, 0xB0)
            CD2_OFFSET(cCharacterEntity, m_pOwner, 0xC8))
    };
}

#endif // AI_CCHARACTERENTITY_H
