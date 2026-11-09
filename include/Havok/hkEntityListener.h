// STAND-IN: reference Havok interface, five slots and a four-byte vptr. CD2's base table is 0x82103E08.
// The beacon deleting wrapper restores this table inline at +0xE40, without a separate base-destructor call.
#ifndef HAVOK_HKENTITYLISTENER_H
#define HAVOK_HKENTITYLISTENER_H
#include "cd2/layout.h"
class hkEntity;
class hkEntityListener
{
public:
    virtual ~hkEntityListener() {}
    virtual void entityAddedCallback(hkEntity *);
    virtual void entityRemovedCallback(hkEntity *);
    virtual void entityShapeSetCallback(hkEntity *);
    virtual void entityDeletedCallback(hkEntity *);
    CD2_LAYOUT_CHECKS(hkEntityListener, CD2_SIZE(hkEntityListener, 4))
};
#endif
