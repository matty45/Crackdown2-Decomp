// STAND-IN: Havok phantom base, slots from Burn's Havok headers (destructor, getType, calcAabb, the overlapping-
// collidable set, clone, updateShapeCollectionFilter). Used through pointers only; its size is not asserted.
#ifndef HAVOK_HKPHANTOM_H
#define HAVOK_HKPHANTOM_H
#include "Havok/hkWorldObject.h"
class hkAabb;
class hkPhantom : public hkWorldObject
{
public:
    virtual ~hkPhantom();
    virtual int getType() const = 0;
    virtual void calcAabb(hkAabb &) = 0;
    virtual void addOverlappingCollidable(hkCollidable *) = 0;
    virtual bool isOverlappingCollidableAdded(hkCollidable *) = 0;
    virtual void removeOverlappingCollidable(hkCollidable *) = 0;
    virtual hkPhantom *clone() = 0;
    virtual void updateShapeCollectionFilter();
};
#endif
