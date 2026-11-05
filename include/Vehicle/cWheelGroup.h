// Vehicle::cWheelGroup (Crackdown 2): base cLandVehicle (RuffKing), size 0x2A30: CD2's descriptor factory (0x826E1FF0)
// builds cClass(0x641, "cWheelGroup", 0x2A30), RuffKing's size. Fields not modelled.
#ifndef VEHICLE_CWHEELGROUP_H
#define VEHICLE_CWHEELGROUP_H

#include "cd2/layout.h"
#include "Vehicle/cLandVehicle.h"

namespace Vehicle
{
    class cWheelGroup : public cLandVehicle
    {
    public:
        // Name and base from RuffKing, which adds no fields (size 0x440). CD2's cCarPrototype constructor (0x826B7BE0)
        // calls cLandVehiclePrototype's directly, so this constructor is inline.
        class cWheelGroupPrototype : public cLandVehicle::cLandVehiclePrototype
        {
        public:
            cWheelGroupPrototype(const RWS::CAttributePacket &packet) : cLandVehiclePrototype(packet) {}

            CD2_LAYOUT_CHECKS(cWheelGroupPrototype,
                CD2_SIZE(cWheelGroupPrototype, 0x440))
        };

        // CD2 0x826E1FF0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled28C0[0x2A30 - 0x28C0];

        CD2_LAYOUT_CHECKS(cWheelGroup,
            CD2_SIZE(cWheelGroup, 0x2A30))
    };
}

#endif
