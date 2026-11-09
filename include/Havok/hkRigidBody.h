// STAND-IN: opaque Havok rigid-body declaration for the primary hkEntity conversion and external calls.
// cBody's reference-named m_pRigidBody has this type; the beacon's PreAddToPhysicsWorld calls the entity API.
// No fields or complete object size are modelled or used.
#ifndef HAVOK_HKRIGIDBODY_H
#define HAVOK_HKRIGIDBODY_H
#include "Havok/hkEntity.h"
class hkRigidBody : public hkEntity
{
};
#endif
