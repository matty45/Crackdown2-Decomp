// hkTransform: rotation and translation (common/hkmath/linear/hktransform.h). Layout from the RuffKing PDB: the
// hkRotation at 0, the translation at 0x30. The constructor from a quaternion stores the translation, then calls
// hkRotation::set, as CD2's IDENTITY_TRANSFORM initializer does.
#ifndef HAVOK_HKTRANSFORM_H
#define HAVOK_HKTRANSFORM_H

#include "Havok/hkRotation.h"

class hkTransform
{
public:
    hkTransform() {}
    hkTransform(const hkQuaternion &q, const hkVector4 &t) : m_translation(t) { m_rotation.set(q); }

private:
    hkRotation m_rotation;
    hkVector4 m_translation;

    CD2_LAYOUT_CHECKS(hkTransform,
        CD2_SIZE(hkTransform, 0x40)
        CD2_OFFSET(hkTransform, m_translation, 0x30))
};

#endif // HAVOK_HKTRANSFORM_H
