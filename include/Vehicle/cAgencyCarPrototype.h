// STAND-IN: RuffKing names this namespace-level prototype and its cCarPrototype base.
// CD2 agency prototype constructors share the car prototype constructor at 0x826B7BE0.
// Interface only: the complete instance storage is unrecovered, so this is not an allocation layout.
#ifndef VEHICLE_CAGENCYCARPROTOTYPE_H
#define VEHICLE_CAGENCYCARPROTOTYPE_H
#include "Vehicle/cCar.h"
namespace Vehicle
{
    class cAgencyCarPrototype : public cCar::cCarPrototype {};
}
#endif
