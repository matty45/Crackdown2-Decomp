// hkQuaternion: Havok's rotation quaternion (common/hkmath/linear/hkquaternion.h). Layout from the RuffKing PDB: one
// hkVector4, m_vec, holding (x, y, z, w).
#ifndef HAVOK_HKQUATERNION_H
#define HAVOK_HKQUATERNION_H

#include "Havok/hkVector4.h"

class hkQuaternion
{
public:
    hkQuaternion() {}
    hkQuaternion(hkReal x, hkReal y, hkReal z, hkReal w) : m_vec(x, y, z, w) {}

    hkVector4 m_vec;

    CD2_LAYOUT_CHECKS(hkQuaternion,
        CD2_SIZE(hkQuaternion, 0x10))
};

#endif // HAVOK_HKQUATERNION_H
