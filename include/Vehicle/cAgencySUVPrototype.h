// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x8213813C; slot 5 is Init at 0x826FBC28.
// Interface only: complete instance storage is unrecovered; do not use this type for allocation.
#ifndef VEHICLE_CAGENCYSUVPROTOTYPE_H
#define VEHICLE_CAGENCYSUVPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencySUVPrototype : public cAgencyCarPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
