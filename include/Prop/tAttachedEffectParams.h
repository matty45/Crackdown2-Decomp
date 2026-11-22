// STAND-IN: reference names/order. CD2 UnAttachEffects (0x8272C5A0) reads
// the turn-off byte at effect +0x5C, or parameters +0x4C. The reference
// matrix/frame layout makes these parameters 0x60 bytes, aligned to 16.
#ifndef PROP_TATTACHEDEFFECTPARAMS_H
#define PROP_TATTACHEDEFFECTPARAMS_H
#include "fun_runtime/mtx.h"
#include "GameRenderer/cFrame.h"
namespace Prop
{
    enum etAttachType
    {
        eAT_None = 0,
        eAT_UseParentOrientation,
        eAT_UseFrame,
        eAT_Max,
    };

    struct tAttachedEffectParams
    {
        tAttachedEffectParams();
        Fun_Runtime::Mtx m_Offset;
        cFrame m_Frame;
        float m_fPriotity; // Reference spelling.
        unsigned char m_nTurnOffFlags;
        etAttachType m_eAttachType;
        bool m_bCullable;
        CD2_LAYOUT_CHECKS(tAttachedEffectParams,
            CD2_SIZE(tAttachedEffectParams, 0x60)
            CD2_OFFSET(tAttachedEffectParams, m_Frame, 0x40)
            CD2_OFFSET(tAttachedEffectParams, m_fPriotity, 0x48)
            CD2_OFFSET(tAttachedEffectParams, m_nTurnOffFlags, 0x4C)
            CD2_OFFSET(tAttachedEffectParams, m_eAttachType, 0x50)
            CD2_OFFSET(tAttachedEffectParams, m_bCullable, 0x54))
    };
}
#endif
