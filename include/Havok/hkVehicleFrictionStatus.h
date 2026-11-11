// Reference Havok friction-status storage: two 36-byte axis records.
#ifndef HAVOK_HKVEHICLEFRICTIONSTATUS_H
#define HAVOK_HKVEHICLEFRICTIONSTATUS_H
#include "cd2/layout.h"
struct hkVehicleFrictionStatus
{
    struct AxisStatus
    {
        float m_forward_slip_velocity;
        float m_side_slip_velocity;
        float m_skid_energy_density;
        float m_side_force;
        float m_delayed_forward_impulse;
        float m_sideRhs;
        float m_forwardRhs;
        float m_relativeSideForce;
        float m_relativeForwardForce;
        CD2_LAYOUT_CHECKS(AxisStatus, CD2_SIZE(AxisStatus, 0x24))
    };
    AxisStatus m_axis[2];
    CD2_LAYOUT_CHECKS(hkVehicleFrictionStatus, CD2_SIZE(hkVehicleFrictionStatus, 0x48))
};
#endif
