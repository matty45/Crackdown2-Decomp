// STAND-IN: RuffKing layout and sole virtual, inherited by cPositionalProxy.
#ifndef CD2_NETWORK_CBASEPROXY_H
#define CD2_NETWORK_CBASEPROXY_H
#include "cd2/layout.h"
class cBaseProxy
{
public:
    virtual void ResetProxy();
    unsigned int m_BaseProxyFlags;
    unsigned int m_CurrentUpdateTime;
    unsigned int m_LastUpdateTime;
    unsigned char m_Owner;
    unsigned char m_Lod;
    CD2_LAYOUT_CHECKS(cBaseProxy, CD2_SIZE(cBaseProxy, 0x14))
};
#endif
