// Reference Havok collidable layout; no instances are constructed by the current decompilation.
#ifndef HAVOK_HKCOLLIDABLE_H
#define HAVOK_HKCOLLIDABLE_H
#include "Havok/hkCdBody.h"
#include "Havok/hkTypedBroadPhaseHandle.h"
class hkCollidable : public hkCdBody
{
protected:
    int m_ownerOffset;
    hkTypedBroadPhaseHandle m_broadPhaseHandle;
public:
    float m_allowedPenetrationDepth;
    CD2_LAYOUT_CHECKS(hkCollidable,
        CD2_SIZE(hkCollidable, 0x24)
        CD2_OFFSET(hkCollidable, m_broadPhaseHandle, 0x14))
};
#endif
