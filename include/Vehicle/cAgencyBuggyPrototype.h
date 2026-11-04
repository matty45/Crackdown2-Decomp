// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x82136B00; slot 5 is Init at 0x826E9AE0.
// Interface only: complete instance storage is unrecovered; do not use this type for allocation.
#ifndef VEHICLE_CAGENCYBUGGYPROTOTYPE_H
#define VEHICLE_CAGENCYBUGGYPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencyBuggyPrototype : public cAgencyCarPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
