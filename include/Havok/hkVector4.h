// hkVector4: Havok's four-float SIMD vector (common/hkmath/linear/hkvector4.h). Layout from the RuffKing PDB: one
// 16-byte-aligned __vector4, m_quad. CD2 builds a vector from constant components with one lvx128 of a 16-byte
// constant and one stvx128 (the physicsproject.h constants), which this inline constructor reproduces.
#ifndef HAVOK_HKVECTOR4_H
#define HAVOK_HKVECTOR4_H

#include <vectorintrinsics.h>
#include "cd2/layout.h"

typedef float hkReal;
typedef __vector4 hkQuadReal;

class hkVector4
{
public:
    hkVector4() {}
    hkVector4(hkReal x, hkReal y, hkReal z, hkReal w = 0.0f)
    {
        __declspec(align(16)) hkReal q[4] = { x, y, z, w };
        m_quad = __lvx(q, 0);
    }
    hkVector4(const hkVector4 &v) { m_quad = v.m_quad; }
    void operator=(const hkVector4 &v) { m_quad = v.m_quad; }

private:
    hkQuadReal m_quad;

    CD2_LAYOUT_CHECKS(hkVector4,
        CD2_SIZE(hkVector4, 0x10))
};

#endif // HAVOK_HKVECTOR4_H
