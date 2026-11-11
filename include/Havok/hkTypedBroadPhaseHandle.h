// Reference typed broad-phase handle; hkCollidable embeds it at +0x14.
#ifndef HAVOK_HKTYPEDBROADPHASEHANDLE_H
#define HAVOK_HKTYPEDBROADPHASEHANDLE_H
#include "Havok/hkBroadPhaseHandle.h"
class hkTypedBroadPhaseHandle : public hkBroadPhaseHandle
{
protected:
    char m_type;
    char m_ownerOffset;
public:
    unsigned short m_objectQualityType;
    unsigned int m_collisionFilterInfo;
    CD2_LAYOUT_CHECKS(hkTypedBroadPhaseHandle,
        CD2_SIZE(hkTypedBroadPhaseHandle, 0xC)
        CD2_OFFSET(hkTypedBroadPhaseHandle, m_collisionFilterInfo, 8))
};
#endif
