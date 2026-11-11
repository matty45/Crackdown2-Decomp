// Reference Havok motion-state storage. Its 0xB0-byte aligned layout places rigid velocity at +0xD0.
#ifndef HAVOK_HKMOTIONSTATE_H
#define HAVOK_HKMOTIONSTATE_H
#include "Havok/hkTransform.h"
#include "Havok/hkSweptTransform.h"
class hkMotionState
{
protected:
    hkTransform m_transform;
    hkSweptTransform m_sweptTransform;
public:
    hkVector4 m_deltaAngle;
    float m_objectRadius;
    float m_maxLinearVelocity;
    float m_maxAngularVelocity;
    unsigned short m_deactivationClass;
    unsigned short m_deactivationCounter;
    CD2_LAYOUT_CHECKS(hkMotionState,
        CD2_SIZE(hkMotionState, 0xB0)
        CD2_OFFSET(hkMotionState, m_deltaAngle, 0x90))
};
#endif
