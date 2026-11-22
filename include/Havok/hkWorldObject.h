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
    const hkCollidable *getCollidable() const { return &m_collidable; }
    // RuffKing's (Havok's) name; CD2 0x82BD22E0 (30 callers), called by cEquipment::EnterGhostState as RuffKing's.
    void addReference();
    hkCollidable *getCollidableRw() { return &m_collidable; }
protected:
    virtual hkMotionState *getMotionState() = 0;
public:
    // Read directly by game code: cEquipment::EnterGhostState (0x82605B90) tests its rigid body's world with an
    // unsigned compare of the loaded word, where an inline accessor's result compares signed (cmpwi).
    hkWorld *m_world;
protected:
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
