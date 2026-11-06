// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x821361AC after calling the shared base prototype constructor 0x826B7BE0.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x826E32F0).
// MakeNew (0x826E2370) allocates 0x670 and calls the constructor (0x826E23F0) out of line; own fields are not recovered.
#ifndef CD2_UNKNOWN_CAGENCYATVPROTOTYPE_H
#define CD2_UNKNOWN_CAGENCYATVPROTOTYPE_H
#include "Vehicle/cCar.h"
namespace unknown
{
    class cAgencyATVPrototype : public Vehicle::cCar::cCarPrototype
    {
    public:
        cAgencyATVPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled4B0[0x670 - 0x4B0];

        CD2_LAYOUT_CHECKS(cAgencyATVPrototype,
            CD2_SIZE(cAgencyATVPrototype, 0x670))
    };
}
#endif
