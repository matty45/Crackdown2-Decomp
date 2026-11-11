// STAND-IN: reference Havok vehicle-instance layout, with its full primary base chain.
// CD2 land-vehicle queries confirm m_deviceStatus (+0xA0) and m_isReversing (+0xD0);
// SetSteeringAngle's callee (0x8269AD68) confirms m_data, m_steering and m_mainSteeringAngle.
#ifndef HAVOK_HKVEHICLEINSTANCE_H
#define HAVOK_HKVEHICLEINSTANCE_H
#include "Havok/hkUnaryAction.h"
#include "Havok/hkBool.h"
#include "Havok/hkVehicleFrictionStatus.h"
#include "Havok/hkVehicleDriverInputStatus.h"
class hkVehicleData; class hkVehicleDriverInput; class hkVehicleSteering; class hkVehicleEngine;
class hkVehicleTransmission; class hkVehicleBrake; class hkVehicleSuspension; class hkVehicleAerodynamics;
class hkVehicleWheelCollide; class hkTyremarksInfo; class hkRigidBody; class hkVehicleVelocityDamper;
class hkVector4; class hkQuaternion;
class hkVehicleInstance : public hkUnaryAction
{
public:
    struct WheelInfo;
    virtual ~hkVehicleInstance();
    virtual void init();
    virtual void applyAction(const hkStepInfo &);
    virtual hkAction *clone(const hkArray<hkEntity *> &, const hkArray<hkPhantom *> &);
    virtual void getPhantoms(hkArray<hkPhantom *> &);
    virtual void calcCurrentPositionAndRotation(const hkRigidBody *, const hkVehicleSuspension *, int, hkVector4 &, hkQuaternion &);
    virtual float calcRPM() const;
    virtual float calcKMPH() const;
    virtual float calcMPH() const;
    virtual void calcStatistics(hkStatisticsCollector *) const;
    hkVehicleData *m_data;
    hkVehicleDriverInput *m_driverInput;
    hkVehicleSteering *m_steering;
    hkVehicleEngine *m_engine;
    hkVehicleTransmission *m_transmission;
    hkVehicleBrake *m_brake;
    hkVehicleSuspension *m_suspension;
    hkVehicleAerodynamics *m_aerodynamics;
    hkVehicleWheelCollide *m_wheelCollide;
    hkTyremarksInfo *m_tyreMarks;
    hkRigidBody *m_chassis;
    hkVehicleVelocityDamper *m_velocityDamper;
    hkArray<WheelInfo> m_wheelsInfo;
    hkVehicleFrictionStatus m_frictionStatus;
    hkVehicleDriverInputStatus *m_deviceStatus;
    hkArray<hkBool> m_isFixed;
    float m_wheelsTimeSinceMaxPedalInput;
    hkBool m_tryingToReverse;
    float m_torque;
    float m_rpm;
    float m_mainSteeringAngle;
    hkArray<float> m_wheelsSteeringAngle;
    hkBool m_isReversing;
    char m_currentGear;
    hkBool m_delayed;
    float m_clutchDelayCountdown;
    CD2_LAYOUT_CHECKS(hkVehicleInstance,
        CD2_SIZE(hkVehicleInstance, 0xD8)
        CD2_OFFSET(hkVehicleInstance, m_data, 0x1C)
        CD2_OFFSET(hkVehicleInstance, m_steering, 0x24)
        CD2_OFFSET(hkVehicleInstance, m_deviceStatus, 0xA0)
        CD2_OFFSET(hkVehicleInstance, m_isReversing, 0xD0))
};
#endif
