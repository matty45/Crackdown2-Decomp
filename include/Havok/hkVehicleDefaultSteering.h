// Reference layout; CD2 cCustomVehicleInstance::SetSteeringAngle (0x8269AD68) reads the wheel mask at +0x10.
#ifndef HAVOK_HKVEHICLEDEFAULTSTEERING_H
#define HAVOK_HKVEHICLEDEFAULTSTEERING_H
#include "Havok/hkVehicleSteering.h"
#include "Havok/hkArray.h"
class hkVehicleDefaultSteering : public hkVehicleSteering
{
public:
    virtual ~hkVehicleDefaultSteering();
    virtual void calcSteering(float, const hkVehicleInstance *, const hkVehicleDriverInput::FilteredDriverInputOutput &, SteeringAnglesOutput &);
    virtual void calcMainSteeringAngle(float, const hkVehicleInstance *, const hkVehicleDriverInput::FilteredDriverInputOutput &, SteeringAnglesOutput &);
    float m_maxSteeringAngle;
    float m_maxSpeedFullSteeringAngle;
    hkArray<hkBool> m_doesWheelSteer;
    CD2_LAYOUT_CHECKS(hkVehicleDefaultSteering,
        CD2_SIZE(hkVehicleDefaultSteering, 0x1C)
        CD2_OFFSET(hkVehicleDefaultSteering, m_maxSteeringAngle, 8)
        CD2_OFFSET(hkVehicleDefaultSteering, m_doesWheelSteer, 0x10))
};
#endif
