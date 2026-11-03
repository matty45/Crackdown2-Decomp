// STAND-IN: RuffKing fields; CD2 unchanged positional-proxy table at 0x420, next base at 0x510.
#ifndef CD2_NETWORK_CPOSITIONALPROXY_H
#define CD2_NETWORK_CPOSITIONALPROXY_H
#include "Network/cBaseProxy.h"
#include <ppcintrinsics.h>
__declspec(align(16)) class cPositionalProxy : public cBaseProxy
{
public:
    virtual void ResetProxy();
    struct SProxyData
    {
        __vector4 m_Position;
        __vector4 m_Velocity;
        __vector4 m_Orientation;
        __vector4 m_AngularVelocity;
    };
    SProxyData m_CurrentData;
    SProxyData m_PreviousData;
    SProxyData m_RenderData;
    float m_PositionBlendFraction;
    float m_OrientationBlendFraction;
    float m_MaxBlendVelocityMagnitude;
    float m_MaxBlendAngVelocityMagnitude;
    CD2_LAYOUT_CHECKS(cPositionalProxy, CD2_SIZE(cPositionalProxy, 0xF0)
        CD2_OFFSET(cPositionalProxy, m_CurrentData, 0x20))
};
#endif
