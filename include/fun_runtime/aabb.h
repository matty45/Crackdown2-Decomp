// Fun_Runtime::tAABB: an axis-aligned bounding box, two 16-byte vectors (0x20 bytes, so 16-byte aligned). Members and
// size from Burn's PDB. In CD2, GOM::cObjectPrototype's constructor (0x82654118) initialises one at 0x50 with two
// whole-vector stores (stvx128 to 0x50 and 0x60).
#ifndef FUN_RUNTIME_AABB_H
#define FUN_RUNTIME_AABB_H

#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace Fun_Runtime
{
    struct tAABB
    {
        Fun_Runtime::Vec3 vecMin;
        Fun_Runtime::Vec3 vecMax;

        CD2_LAYOUT_CHECKS(tAABB,
            CD2_SIZE(tAABB, 0x20)
            CD2_OFFSET(tAABB, vecMax, 0x10))
    };
}

#endif // FUN_RUNTIME_AABB_H
