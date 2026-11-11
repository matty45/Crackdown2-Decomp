// STAND-IN: pointer-only primary-base conversion, named by Burn's Havok world-object declaration.
// The reference storage is now modelled in full; CD2 hkEntity::m_motion at +0x50 confirms its extent.
#ifndef HAVOK_HKWORLDOBJECT_H
#define HAVOK_HKWORLDOBJECT_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkLinkedCollidable.h"
#include "Havok/hkWorldOperation.h"
class hkWorld;
class hkMotionState;
struct hkProperty;
class hkWorldObject : public hkReferencedObject
{
public:
    virtual hkWorldOperation::Result setShape(hkShape *);
protected:
    virtual hkMotionState *getMotionState() = 0;
    hkWorld *m_world;
    void *m_userData;
    const char *m_name;
    hkLinkedCollidable m_collidable;
    hkArray<hkProperty> m_properties;
    CD2_LAYOUT_CHECKS(hkWorldObject,
        CD2_SIZE(hkWorldObject, 0x50)
        CD2_OFFSET(hkWorldObject, m_collidable, 0x14)
        CD2_OFFSET(hkWorldObject, m_properties, 0x44))
};
#endif
