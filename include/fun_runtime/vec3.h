// Fun_Runtime::Vec3: 16-byte vector. RuffKing's class wraps a private __vector4 with accessor methods; this stand-in
// exposes the same storage as both the __vector4 and x/y/z/w so code can use either view.
// Verified via Equip::cFlocket (the copy constructor below reproduces CD2's whole-vector copy followed by the
// x, w = 0, y, z stores), VFX::cAmbientVFXSpawner and VEHICLE_CONTROL::cHelicopterController.
#ifndef FUN_RUNTIME_VEC3_H
#define FUN_RUNTIME_VEC3_H

#include <ppcintrinsics.h>
#include "fun_runtime/oldvec3.h"

namespace Fun_Runtime
{
    __declspec(align(16)) class Vec3
    {
    public:
        union
        {
            __vector4 v;
            struct { float x, y, z, w; };
        };

        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(const Vec3 &o) : v(o.v) { x = o.x; w = 0.0f; y = o.y; z = o.z; }
        // RuffKing declares Vec3(const OldVec3 &); w = 1.0 as in RuffKing's Vec3(float, float, float). CD2's
        // AI::cPedestrianBase constructor builds two members from ZeroVec this way: each component read after the
        // previous store (a reference source), then w = 1.0.
        Vec3(const OldVec3 &o) : x(o.x), y(o.y), z(o.z), w(1.0f) {}
    };
}

#endif // FUN_RUNTIME_VEC3_H
