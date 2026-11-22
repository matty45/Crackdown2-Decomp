// STAND-IN: reference names/order. CD2 UnAttachEffects scans six 0x70-byte
// records at cProp +0xB00, testing each instance at +0 and flags at +0x5C.
// Release (0x8272C5F8) is the reference-named per-record cleanup function.
#ifndef PROP_TATTACHEDEFFECT_H
#define PROP_TATTACHEDEFFECT_H
#include "Prop/tAttachedEffectParams.h"
namespace VFX { class cParticleEffectInstance; }
namespace Prop
{
    struct tAttachedVFXHandle;
    struct tAttachedEffect
    {
        tAttachedEffect();
        void Release();
        VFX::cParticleEffectInstance *m_pInstance;
        tAttachedVFXHandle *pHandle;
        tAttachedEffectParams m_Params;
        CD2_LAYOUT_CHECKS(tAttachedEffect,
            CD2_SIZE(tAttachedEffect, 0x70)
            CD2_OFFSET(tAttachedEffect, m_pInstance, 0)
            CD2_OFFSET(tAttachedEffect, pHandle, 4)
            CD2_OFFSET(tAttachedEffect, m_Params, 0x10))
    };
}
#endif
