// Reference field names; CD2 IsHandbrakeOn (0x826C48D0) reads the handbrake byte at +0x10.
#ifndef HAVOK_HKVEHICLEDRIVERINPUTANALOGSTATUS_H
#define HAVOK_HKVEHICLEDRIVERINPUTANALOGSTATUS_H
#include "Havok/hkVehicleDriverInputStatus.h"
#include "Havok/hkBool.h"
class hkVehicleDriverInputAnalogStatus : public hkVehicleDriverInputStatus
{
public:
    virtual ~hkVehicleDriverInputAnalogStatus();
    virtual hkVehicleDriverInputStatus *clone();
    float m_positionX;
    float m_positionY;
    hkBool m_handbrakeButtonPressed;
    hkBool m_reverseButtonPressed;
    CD2_LAYOUT_CHECKS(hkVehicleDriverInputAnalogStatus,
        CD2_SIZE(hkVehicleDriverInputAnalogStatus, 0x14)
        CD2_OFFSET(hkVehicleDriverInputAnalogStatus, m_handbrakeButtonPressed, 0x10))
};
#endif
