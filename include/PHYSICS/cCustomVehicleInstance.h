// STAND-IN: cCustomVehicleInstance derives from hkVehicleInstance (Burn/RuffKing).
// Own regions remain opaque; CD2 IsBraking and SetEngineDamage confirm the named fields at +0x202/+0x2D8.
// Used only through pointers; complete allocation size and the remaining members are not asserted.
#ifndef PHYSICS_CCUSTOMVEHICLEINSTANCE_H
#define PHYSICS_CCUSTOMVEHICLEINSTANCE_H
#include "Havok/hkVehicleInstance.h"
namespace PHYSICS
{
    class cCustomVehicleInstance : public hkVehicleInstance
    {
    public:
        // CD2 table 0x82133048: slots 9 and 4, installed by the constructor at 0x82699680.
        virtual float calcRPM() const;
        virtual float calcMPH() const;
        virtual void getPhantoms(hkArray<hkPhantom *> &);
        void SetSteeringAngle(float);
        // Reference signatures return hkBool by value. CD2 preserves the signed byte conversion
        // through that returned object in cLandVehicle::IsReversing and IsBraking.
        hkBool IsReversing() const { return m_isReversing; }
        hkBool IsBraking() const { return m_bIsBraking; }
    private:
        unsigned char m_unmodelledD8[0x200 - 0xD8];
    public:
        hkBool m_bInAir;
        hkBool m_bWheelSpinMode;
        hkBool m_bIsBraking;
    private:
        unsigned char m_unmodelled203[0x2D8 - 0x203];
    public:
        float m_DamageTorqueEfficiencyMultiplier;
        CD2_LAYOUT_CHECKS(cCustomVehicleInstance,
            CD2_OFFSET(cCustomVehicleInstance, m_bIsBraking, 0x202)
            CD2_OFFSET(cCustomVehicleInstance, m_DamageTorqueEfficiencyMultiplier, 0x2D8))
    };
}
#endif
