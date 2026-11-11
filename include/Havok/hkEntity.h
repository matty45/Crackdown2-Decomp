// STAND-IN: opaque Havok entity declaration for external calls only. CD2's beacon hook at 0x8245C5C8
// passes its rigid body and entity-listener subobject to addEntityListener (0x82BD1778).
// The prefix now includes the reference-named motion pointer at +0x50, read by CD2 calcMPH.
// Remaining entity fields and complete size are not asserted; the type is used only through pointers.
#ifndef HAVOK_HKENTITY_H
#define HAVOK_HKENTITY_H
#include "Havok/hkWorldObject.h"
class hkEntityListener;
class hkMotion;
class hkEntity : public hkWorldObject
{
public:
    void addEntityListener(hkEntityListener *);
    virtual hkMotionState *getMotionState();
    virtual void deallocateInternalArrays();
protected:
    hkMotion *m_motion;
    CD2_LAYOUT_CHECKS(hkEntity, CD2_OFFSET(hkEntity, m_motion, 0x50))
};
#endif
