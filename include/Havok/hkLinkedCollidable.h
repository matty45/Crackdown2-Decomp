// Reference linked collidable; its full 0x30-byte storage determines hkWorldObject's size.
#ifndef HAVOK_HKLINKEDCOLLIDABLE_H
#define HAVOK_HKLINKEDCOLLIDABLE_H
#include "Havok/hkCollidable.h"
#include "Havok/hkArray.h"
struct hkAgentNnEntry;
class hkLinkedCollidable : public hkCollidable
{
public:
    struct CollisionEntry
    {
        hkAgentNnEntry *m_agentEntry;
        hkLinkedCollidable *m_partner;
        CD2_LAYOUT_CHECKS(CollisionEntry, CD2_SIZE(CollisionEntry, 8))
    };
    hkArray<CollisionEntry> m_collisionEntries;
    CD2_LAYOUT_CHECKS(hkLinkedCollidable,
        CD2_SIZE(hkLinkedCollidable, 0x30)
        CD2_OFFSET(hkLinkedCollidable, m_collisionEntries, 0x24))
};
#endif
