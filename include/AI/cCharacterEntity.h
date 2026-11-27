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
//   - "SetPlayerViewingDistance" (0x823F0608) stores 0x94, RuffKing's m_fPlayerViewingDistance there.
//   - "SetViewingAngle" (0x823F05B0) expands RuffKing's SetViewingAngle: the angle at 0x88 and the cosine of its
//     radians at 0x8C, RuffKing's m_fCosViewingAngle.
//   - m_attrWidth (0x70) and m_attrHeight (0x74): RuffKing's names and offsets; "RetHeight" (0x823F03E8) returns the
//     height attribute's value and RetRadius (0x823F03F8) half the width attribute's.
#ifndef AI_CCHARACTERENTITY_H
#define AI_CCHARACTERENTITY_H

#include <math.h>
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
#include "Kaim/CEntity.h"
#include "Kaim/CEntityWidth.h"
#include "Kaim/CEntityHeight.h"

namespace Fun_Runtime { class cScriptHost; }

namespace AI
{
    class cCharacterEntityIF;

    class cCharacterEntity : public Kaim::CEntity
    {
    private:
        unsigned char m_pad0[0x4];
    public:
        // CD2 0x823238B0 takes the script interface: it queries the registered
        // class at +0x14 and reaches the owning game object through its -0x1C base adjustment.
        bool IsInViewCone(Fun_Runtime::cScriptHost *object);
        const char *m_name;                         // 0x4
    private:
        unsigned char m_pad8[0x70 - 0x8];
    public:
        Kaim::CEntityWidth *m_attrWidth;            // 0x70
        Kaim::CEntityHeight *m_attrHeight;          // 0x74
    private:
        unsigned char m_pad78[0x88 - 0x78];
    public:
        float m_fViewingAngle;                      // 0x88
        float m_fCosViewingAngle;                   // 0x8C
        // RuffKing's (out of line there); the "SetViewingAngle" script method expands it.
        void SetViewingAngle(float fAngle)
        {
            m_fViewingAngle = fAngle;
            m_fCosViewingAngle = cosf(fAngle * 0.017453f);
        }
        float m_fViewingDistance;                   // 0x90
        float m_fPlayerViewingDistance;             // 0x94
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
            CD2_OFFSET(cCharacterEntity, m_attrWidth, 0x70)
            CD2_OFFSET(cCharacterEntity, m_attrHeight, 0x74)
            CD2_OFFSET(cCharacterEntity, m_fViewingAngle, 0x88)
            CD2_OFFSET(cCharacterEntity, m_fCosViewingAngle, 0x8C)
            CD2_OFFSET(cCharacterEntity, m_fViewingDistance, 0x90)
            CD2_OFFSET(cCharacterEntity, m_fPlayerViewingDistance, 0x94)
            CD2_OFFSET(cCharacterEntity, m_fThreatObjectViewingDistance, 0x98)
            CD2_OFFSET(cCharacterEntity, m_fHearingAcuteness, 0x9C)
            CD2_OFFSET(cCharacterEntity, m_vecHeadDirection, 0xA0)
            CD2_OFFSET(cCharacterEntity, m_vecEyePosition, 0xB0)
            CD2_OFFSET(cCharacterEntity, m_pOwner, 0xC8))
    };
}

#endif // AI_CCHARACTERENTITY_H
