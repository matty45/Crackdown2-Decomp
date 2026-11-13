// Reference Havok collision-body storage; the motion pointer can name a transform or motion state.
#ifndef HAVOK_HKCDBODY_H
#define HAVOK_HKCDBODY_H
#include "cd2/layout.h"
class hkShape;
class hkCdBody
{
public:
    const hkShape *getShape() const { return m_shape; }
protected:
    const hkShape *m_shape;
    unsigned int m_shapeKey;
    const void *m_motion;
    const hkCdBody *m_parent;
    CD2_LAYOUT_CHECKS(hkCdBody,
        CD2_SIZE(hkCdBody, 0x10)
        CD2_OFFSET(hkCdBody, m_motion, 8))
};
#endif
