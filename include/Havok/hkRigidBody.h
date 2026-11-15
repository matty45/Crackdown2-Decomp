// STAND-IN: opaque Havok rigid-body declaration for the primary hkEntity conversion and external calls.
// cBody's reference-named m_pRigidBody has this type; the beacon's PreAddToPhysicsWorld calls the entity API.
// No fields or complete object size are modelled or used.
#ifndef HAVOK_HKRIGIDBODY_H
#define HAVOK_HKRIGIDBODY_H
#include "Havok/hkEntity.h"
#include "Havok/hkRigidMotion.h"
class hkRigidBody : public hkEntity
{
public:
    // CD2 0x82BD2DC0; motion-type interface name agrees with the reference Havok API.
    // The final enum types are not recovered yet; moving-platform 0x8273AD74 passes 1 and 0.
    void setMotionType(hkMotion::MotionType type, int activationState, int collisionFilterMode);
    const hkVector4 &getLinearVelocity() const
    {
        return static_cast<const hkRigidMotion *>(m_motion)->getLinearVelocity();
    }
};
#endif
