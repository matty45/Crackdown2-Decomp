// hkVector4: Havok's four-float SIMD vector (common/hkmath/linear/hkvector4.h). Layout from the RuffKing PDB: one
// 16-byte-aligned __vector4, m_quad. CD2 builds a vector from constant components with one lvx128 of a 16-byte
// constant and one stvx128 (the physicsproject.h constants), which this inline constructor reproduces.
#ifndef HAVOK_HKVECTOR4_H
#define HAVOK_HKVECTOR4_H

#include <vectorintrinsics.h>
#include "cd2/layout.h"
#include "Havok/hkSimdReal.h"
#include <math.h>

typedef float hkReal;
typedef __vector4 hkQuadReal;

class hkVector4
{
public:
    // CD2's build of the Havok headers marks a default-constructed vector as uninitialised: every component is
    // (hkReal)0xffffffff (0x4F800000). Evidence: one 16-byte constant of four such words at 0x8216E870, loaded with
    // lvx128 and stored to each default-constructed vector by 127 functions (four stores for a local hkTransform);
    // and IDENTITY_TRANSFORM's rotation, which its constructor default-constructs before hkRotation::set, holds these
    // words in CD2's initialised data in all 994 copies while its initializer stores only the translation. A constant
    // vector assigned whole reproduces both (the compiler folds the stores into the static's initial data); four
    // scalar stores give the same data but stfs instructions at run time, which CD2 does not have.
    hkVector4()
    {
        static const hkQuadReal uninitialised = { (hkReal)0xffffffff, (hkReal)0xffffffff, (hkReal)0xffffffff, (hkReal)0xffffffff };
        m_quad = uninitialised;
    }
    hkVector4(hkReal x, hkReal y, hkReal z, hkReal w = 0.0f)
    {
        __declspec(align(16)) hkReal q[4] = { x, y, z, w };
        m_quad = __lvx(q, 0);
    }
    hkVector4(const hkVector4 &v) { m_quad = v.m_quad; }
    void operator=(const hkVector4 &v) { m_quad = v.m_quad; }
    const hkQuadReal &getQuad() const { return m_quad; }
    hkSimdReal dot3(const hkVector4 &other) const { return hkSimdReal(__vmsum3fp(m_quad, other.m_quad)); }
    hkSimdReal length3() const { return hkSimdReal(sqrtf(__vmsum3fp(m_quad, m_quad).x)); }

private:
    hkQuadReal m_quad;

    CD2_LAYOUT_CHECKS(hkVector4,
        CD2_SIZE(hkVector4, 0x10))
};

#endif // HAVOK_HKVECTOR4_H
