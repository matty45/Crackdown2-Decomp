// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x82138A34; slot 5 is Init at 0x826FCCF8.
// MakeNew (0x826FC6B0) allocates 0x530 and calls the constructor (0x826FC7D0) out of line; own fields are not recovered.
#ifndef VEHICLE_CAGENCYTANKPROTOTYPE_H
#define VEHICLE_CAGENCYTANKPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencyTankPrototype : public cAgencyCarPrototype
    {
    public:
        cAgencyTankPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled4C0[0x530 - 0x4C0];

        CD2_LAYOUT_CHECKS(cAgencyTankPrototype,
            CD2_SIZE(cAgencyTankPrototype, 0x530))
    };
}
#endif
