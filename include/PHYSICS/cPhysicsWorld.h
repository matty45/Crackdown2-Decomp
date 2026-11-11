// STAND-IN: pointer-only physics world. RuffKing's cPhysicsWorld.h declares hkWorld as its primary base.
// No complete layout is asserted or instantiated here.
#ifndef PHYSICS_CPHYSICSWORLD_H
#define PHYSICS_CPHYSICSWORLD_H
#include "Havok/hkWorld.h"
namespace PHYSICS
{
    class cPhysicsWorld : public hkWorld
    {
    };
}
#endif
