// Reference Havok swept-transform storage.
#ifndef HAVOK_HKSWEPTTRANSFORM_H
#define HAVOK_HKSWEPTTRANSFORM_H
#include "Havok/hkQuaternion.h"
class hkSweptTransform
{
public:
    hkVector4 m_centerOfMass0;
    hkVector4 m_centerOfMass1;
    hkQuaternion m_rotation0;
    hkQuaternion m_rotation1;
    hkVector4 m_centerOfMassLocal;
    CD2_LAYOUT_CHECKS(hkSweptTransform, CD2_SIZE(hkSweptTransform, 0x50))
};
#endif
