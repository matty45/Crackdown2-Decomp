// STAND-IN: RuffKing names this prototype and its cAgencyCarPrototype base.
// CD2 MakeNew/constructor installs table 0x82136CC0; slot 5 is Init at 0x826ED338.
// MakeNew (0x826ECF38) allocates 0x500 and calls the constructor (0x826ECFB8) out of line; own fields are not recovered.
#ifndef VEHICLE_CAGENCYSPORTSPROTOTYPE_H
#define VEHICLE_CAGENCYSPORTSPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencySportsPrototype : public cAgencyCarPrototype
    {
    public:
        cAgencySportsPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled4C0[0x500 - 0x4C0];

        CD2_LAYOUT_CHECKS(cAgencySportsPrototype,
            CD2_SIZE(cAgencySportsPrototype, 0x500))
    };
}
#endif
