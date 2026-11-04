// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x82138A34; slot 5 is Init at 0x826FCCF8.
// Interface only: complete instance storage is unrecovered; do not use this type for allocation.
#ifndef VEHICLE_CAGENCYTANKPROTOTYPE_H
#define VEHICLE_CAGENCYTANKPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencyTankPrototype : public cAgencyCarPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
