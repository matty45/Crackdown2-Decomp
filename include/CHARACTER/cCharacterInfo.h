// Reference character-controller dimensions. CD2's complex controller embeds this at +0xE0;
// RetMaxStandheight and RetStandHalfBox confirm its height (+0x20) and AABB (+0x40).
#ifndef CHARACTER_CCHARACTERINFO_H
#define CHARACTER_CCHARACTERINFO_H
#include "Havok/hkVector4.h"
namespace CHARACTER
{
    struct cCharacterInfo
    {
        hkVector4 m_Gravity;
        float m_fEffectDecel;
        float m_fMass;
        float m_fTerminalVelocity;
        float m_fRadius;
        float m_fHeight;
        float m_fHalfHeight;
        float m_fCrouchRadius;
        float m_fCrouchHeight;
        float m_fCrouchHalfHeight;
        float m_fCharSwimHeightPecentage;
        float m_fCharWaterFloatHeightPecentage;
        hkVector4 m_LocalAABB;
        CD2_LAYOUT_CHECKS(cCharacterInfo,
            CD2_SIZE(cCharacterInfo, 0x50)
            CD2_OFFSET(cCharacterInfo, m_fHeight, 0x20)
            CD2_OFFSET(cCharacterInfo, m_LocalAABB, 0x40))
    };
}
#endif
