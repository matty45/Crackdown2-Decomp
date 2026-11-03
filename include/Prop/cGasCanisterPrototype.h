// STAND-IN: RuffKing names/base; CD2 MakeNew (0x82743708) confirms the 0x560-byte
// allocation, identity matrix at 0x500 and scalar defaults at 0x4F0 and 0x540..0x550.
#ifndef PROP_CGASCANISTERPROTOTYPE_H
#define PROP_CGASCANISTERPROTOTYPE_H

#include "Prop/cProp.h"
#include "fun_runtime/mtx.h"

namespace Prop
{
    class cGasCanisterPrototype : public cProp::cPropPrototype
    {
    public:
        // CD2 MakeNew contains this entire constructor, including the identity matrix stores.
        __forceinline cGasCanisterPrototype(const RWS::CAttributePacket &packet)
            : cPropPrototype(packet), m_nPlumeVFX(-1), m_fAcceleration(50.0f),
              m_fMaxForwardSpeed(40.0f), m_fRocketDuration(15.0f),
              m_fValveRadiusSq(0.2f * 0.2f), m_fPlumeScale(5.0f) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        int m_nPlumeVFX;
        Fun_Runtime::Mtx m_mValveLocal;
        float m_fAcceleration;
        float m_fMaxForwardSpeed;
        float m_fRocketDuration;
        float m_fValveRadiusSq;
        float m_fPlumeScale;

        CD2_LAYOUT_CHECKS(cGasCanisterPrototype,
            CD2_SIZE(cGasCanisterPrototype, 0x560)
            CD2_OFFSET(cGasCanisterPrototype, m_nPlumeVFX, 0x4F0)
            CD2_OFFSET(cGasCanisterPrototype, m_mValveLocal, 0x500)
            CD2_OFFSET(cGasCanisterPrototype, m_fAcceleration, 0x540)
            CD2_OFFSET(cGasCanisterPrototype, m_fMaxForwardSpeed, 0x544)
            CD2_OFFSET(cGasCanisterPrototype, m_fRocketDuration, 0x548)
            CD2_OFFSET(cGasCanisterPrototype, m_fValveRadiusSq, 0x54C)
            CD2_OFFSET(cGasCanisterPrototype, m_fPlumeScale, 0x550))
    };
}

#endif
