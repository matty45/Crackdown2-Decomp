// STAND-IN: reference name/interface. CD2 tAttachedEffect::Release (0x8272C5F8)
// calls OnReleased through slot 0; there is no virtual destructor. The reference
// back-pointer follows the vptr, making the handle eight bytes.
#ifndef PROP_TATTACHEDVFXHANDLE_H
#define PROP_TATTACHEDVFXHANDLE_H
#include "cd2/layout.h"
namespace Prop
{
    struct tAttachedEffect;
    struct tAttachedVFXHandle
    {
        tAttachedVFXHandle();
        virtual void OnReleased();
        tAttachedEffect *m_pAttachedEffect;
        CD2_LAYOUT_CHECKS(tAttachedVFXHandle,
            CD2_SIZE(tAttachedVFXHandle, 8)
            CD2_OFFSET(tAttachedVFXHandle, m_pAttachedEffect, 4))
    };
}
#endif
