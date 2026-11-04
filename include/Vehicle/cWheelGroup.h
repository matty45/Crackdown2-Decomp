// STAND-IN: RuffKing names cWheelGroup and its prototype bases.
// Only the shared prototype interface is recovered; neither type is an allocation layout.
#ifndef VEHICLE_CWHEELGROUP_H
#define VEHICLE_CWHEELGROUP_H
#include "Vehicle/cLandVehicle.h"
namespace Vehicle
{
    class cWheelGroup : public cLandVehicle
    {
    public:
        class cWheelGroupPrototype : public cLandVehicle::cLandVehiclePrototype {};
    };
}
#endif
