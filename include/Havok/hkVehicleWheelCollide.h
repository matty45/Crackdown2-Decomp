// Havok wheel-collision interface from RuffKing/Burn. CD2 vehicle getPhantoms (0x82699F60)
// calls slot 4, after collideWheels and init; m_alreadyUsed follows the eight-byte reference-count base.
#ifndef HAVOK_HKVEHICLEWHEELCOLLIDE_H
#define HAVOK_HKVEHICLEWHEELCOLLIDE_H
#include "Havok/hkReferencedObject.h"
#include "Havok/hkArray.h"
#include "Havok/hkBool.h"
class hkVehicleInstance;
class hkPhantom;
class hkVehicleWheelCollide : public hkReferencedObject
{
public:
    struct CollisionDetectionWheelOutput;
    virtual ~hkVehicleWheelCollide();
    virtual void collideWheels(float, hkVehicleInstance *, CollisionDetectionWheelOutput *) = 0;
    virtual void init(const hkVehicleInstance *) = 0;
    virtual void getPhantoms(hkArray<hkPhantom *> &) = 0;
    virtual hkVehicleWheelCollide *clone(const hkArray<hkPhantom *> &) = 0;
    hkBool m_alreadyUsed;
    CD2_LAYOUT_CHECKS(hkVehicleWheelCollide,
        CD2_SIZE(hkVehicleWheelCollide, 0xC)
        CD2_OFFSET(hkVehicleWheelCollide, m_alreadyUsed, 8))
};
#endif
