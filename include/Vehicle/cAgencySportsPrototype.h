// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x82136CC0; slot 5 is Init at 0x826ED338.
// Interface only: complete instance storage is unrecovered; do not use this type for allocation.
#ifndef VEHICLE_CAGENCYSPORTSPROTOTYPE_H
#define VEHICLE_CAGENCYSPORTSPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencySportsPrototype : public cAgencyCarPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
