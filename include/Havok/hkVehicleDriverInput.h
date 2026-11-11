// Reference Havok driver-input interface and its filtered input payload.
#ifndef HAVOK_HKVEHICLEDRIVERINPUT_H
#define HAVOK_HKVEHICLEDRIVERINPUT_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkBool.h"
class hkVehicleInstance;
class hkVehicleDriverInputStatus;
class hkVehicleDriverInput : public hkReferencedObject
{
public:
    struct FilteredDriverInputOutput
    {
        float m_acceleratorPedalInput;
        float m_brakePedalInput;
        float m_steeringWheelInput;
        hkBool m_handbrakeOn;
        hkBool m_tryingToReverse;
        CD2_LAYOUT_CHECKS(FilteredDriverInputOutput, CD2_SIZE(FilteredDriverInputOutput, 0x10))
    };
    virtual ~hkVehicleDriverInput();
    virtual void calcDriverInput(float, const hkVehicleInstance *, const hkVehicleDriverInputStatus *, FilteredDriverInputOutput &) = 0;
    CD2_LAYOUT_CHECKS(hkVehicleDriverInput, CD2_SIZE(hkVehicleDriverInput, 8))
};
#endif
