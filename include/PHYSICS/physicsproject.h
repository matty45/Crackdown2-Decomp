// Physics project constants: Havok vectors defined in the header, one copy per object file. Names, header and order from
// the RuffKing PDB (shared/physics/physicsproject.h, initializers at lines 34-36 and 38-40); values from CD2.
#ifndef PHYSICS_PHYSICSPROJECT_H
#define PHYSICS_PHYSICSPROJECT_H

#include "Havok/hkVector4.h"
#include "Havok/hkQuaternion.h"
#include "Havok/hkTransform.h"

static hkVector4 WORLD_RIGHT_VECTOR(1.0f, 0.0f, 0.0f, 0.0f);
static hkVector4 WORLD_UP_VECTOR(0.0f, 1.0f, 0.0f, 0.0f);
static hkVector4 WORLD_AT_VECTOR(0.0f, 0.0f, 1.0f, 0.0f);

static hkVector4 ZERO_VECTOR(0.0f, 0.0f, 0.0f, 0.0f);
static hkTransform IDENTITY_TRANSFORM(hkQuaternion(0.0f, 0.0f, 0.0f, 1.0f), hkVector4(0.0f, 0.0f, 0.0f, 0.0f));
static hkQuaternion IDENTITY_QUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

#endif // PHYSICS_PHYSICSPROJECT_H
