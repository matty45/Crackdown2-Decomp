// STAND-IN: reference names/base/order. CD2 cProp construction installs this
// one-slot interface at +0xDC8/+0xDE8, 0x20 bytes apart. The respawn helper
// (0x8272C6E0) reads m_pProp at +8 and m_nIndex at +0x1C, then writes +0x18.
#ifndef PROP_TATTACHEDVFXPOINT_H
#define PROP_TATTACHEDVFXPOINT_H
#include "Prop/tAttachedVFXHandle.h"
#include "GameRenderer/cFrame.h"
namespace Prop
{
    class cProp;
    struct tAttachedVFXPoint : public tAttachedVFXHandle
    {
        tAttachedVFXPoint();
        virtual void OnReleased();
        void CalcRandRespawnTime(); // CD2 0x8272C6E0.
    private:
        cProp *m_pProp;
        cFrame m_Frame;
        unsigned int m_nExpireTime;
        unsigned int m_nRespawnTime;
        unsigned char m_nIndex;
        CD2_LAYOUT_CHECKS(tAttachedVFXPoint,
            CD2_SIZE(tAttachedVFXPoint, 0x20)
            CD2_OFFSET(tAttachedVFXPoint, m_pProp, 8)
            CD2_OFFSET(tAttachedVFXPoint, m_Frame, 0xC)
            CD2_OFFSET(tAttachedVFXPoint, m_nExpireTime, 0x14)
            CD2_OFFSET(tAttachedVFXPoint, m_nRespawnTime, 0x18)
            CD2_OFFSET(tAttachedVFXPoint, m_nIndex, 0x1C))
    };
}
#endif
