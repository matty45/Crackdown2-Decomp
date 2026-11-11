// STAND-IN: reference rigid-motion storage over the complete hkMotion base.
// CD2 calcMPH (0x82699F08) reaches linear velocity through hkEntity's motion pointer, then +0xD0.
// Only nonvirtual accessors used by reconstructed code are exposed; this type is never instantiated.
#ifndef HAVOK_HKRIGIDMOTION_H
#define HAVOK_HKRIGIDMOTION_H
#include "Havok/hkMotion.h"
#include "Havok/hkMotionState.h"
class hkRigidMotion : public hkMotion
{
public:
    hkMotionState m_motionState;
    float m_massInv;
    float m_particleMinInertiaDiagInv;
    float m_linearDamping;
    float m_angularDamping;
    hkVector4 m_linearVelocity;
    hkVector4 m_angularVelocity;
    const hkVector4 &getLinearVelocity() const { return m_linearVelocity; }
    CD2_LAYOUT_CHECKS(hkRigidMotion,
        CD2_SIZE(hkRigidMotion, 0xF0)
        CD2_OFFSET(hkRigidMotion, m_motionState, 0x10)
        CD2_OFFSET(hkRigidMotion, m_linearVelocity, 0xD0))
};
#endif
