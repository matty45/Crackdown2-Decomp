// CD2 vehicle-instance source recovered from the reference method names and typed caller/data flow.
// The currently owned range covers the RPM/phantom virtuals, copy helpers and steering setter;
// other methods remain outside this source split.
#include "PHYSICS/cCustomVehicleInstance.h"
#include "Havok/hkVehicleData.h"
#include "Havok/hkVehicleDefaultSteering.h"
#include "Havok/hkVehicleWheelCollide.h"
#include "Havok/hkRigidBody.h"

namespace PHYSICS
{
    float cCustomVehicleInstance::calcRPM() const
    {
        return m_rpm;
    }

    float cCustomVehicleInstance::calcMPH() const
    {
        return float(m_chassis->getLinearVelocity().length3()) * 2.2369974f; // CD2's rounded metres-per-second to MPH factor.
    }

    void cCustomVehicleInstance::getPhantoms(hkArray<hkPhantom *> &phantoms)
    {
        m_wheelCollide->getPhantoms(phantoms);
    }

    void cCustomVehicleInstance::SetSteeringAngle(float angle)
    {
        m_mainSteeringAngle = angle;
        for (int wheel = 0; wheel < m_data->m_numWheels; ++wheel)
        {
            if (static_cast<hkVehicleDefaultSteering *>(m_steering)->m_doesWheelSteer.m_data[wheel])
                m_wheelsSteeringAngle.m_data[wheel] = angle;
        }
    }
}
