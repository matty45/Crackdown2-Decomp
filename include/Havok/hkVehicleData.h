// STAND-IN: pointer-only prefix of hkVehicleData, from the reference layout.
// CD2 SetSteeringAngle (0x8269AD68) reads the signed wheel count at +0x20.
// Remaining fields and the complete allocation size are not asserted; no derived layout uses this prefix.
#ifndef HAVOK_HKVEHICLEDATA_H
#define HAVOK_HKVEHICLEDATA_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkVector4.h"
class hkVehicleData : public hkReferencedObject
{
public:
    hkVector4 m_gravity;
    char m_numWheels;
    CD2_LAYOUT_CHECKS(hkVehicleData,
        CD2_OFFSET(hkVehicleData, m_gravity, 0x10)
        CD2_OFFSET(hkVehicleData, m_numWheels, 0x20))
};
#endif
