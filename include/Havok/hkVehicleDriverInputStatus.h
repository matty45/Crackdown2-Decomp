// Havok driver-input status interface, from Burn/RuffKing; no extra storage over hkReferencedObject.
#ifndef HAVOK_HKVEHICLEDRIVERINPUTSTATUS_H
#define HAVOK_HKVEHICLEDRIVERINPUTSTATUS_H
#include "Havok/hkReferencedObject.h"
class hkVehicleDriverInputStatus : public hkReferencedObject
{
public:
    virtual ~hkVehicleDriverInputStatus();
    virtual hkVehicleDriverInputStatus *clone() = 0;
    CD2_LAYOUT_CHECKS(hkVehicleDriverInputStatus, CD2_SIZE(hkVehicleDriverInputStatus, 8))
};
#endif
