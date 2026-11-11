// Reference Havok steering interface. The subclass's first scalar at +8 confirms the base size.
#ifndef HAVOK_HKVEHICLESTEERING_H
#define HAVOK_HKVEHICLESTEERING_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkVehicleDriverInput.h"
class hkVehicleSteering : public hkReferencedObject
{
public:
    struct SteeringAnglesOutput;
    virtual ~hkVehicleSteering();
    virtual void calcSteering(float, const hkVehicleInstance *, const hkVehicleDriverInput::FilteredDriverInputOutput &, SteeringAnglesOutput &) = 0;
    CD2_LAYOUT_CHECKS(hkVehicleSteering, CD2_SIZE(hkVehicleSteering, 8))
};
#endif
