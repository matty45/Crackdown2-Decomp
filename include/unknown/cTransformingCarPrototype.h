// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x82133C4C after calling the shared base prototype constructor 0x826B7BE0.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x826ADDC0).
// MakeNew (0x826AB4C0) allocates 0x700 and calls the constructor (0x826AD828) out of line; own fields are not recovered.
#ifndef CD2_UNKNOWN_CTRANSFORMINGCARPROTOTYPE_H
#define CD2_UNKNOWN_CTRANSFORMINGCARPROTOTYPE_H
#include "Vehicle/cCar.h"
namespace unknown
{
    class cTransformingCarPrototype : public Vehicle::cCar::cCarPrototype
    {
    public:
        cTransformingCarPrototype(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled4B0[0x700 - 0x4B0];

        CD2_LAYOUT_CHECKS(cTransformingCarPrototype,
            CD2_SIZE(cTransformingCarPrototype, 0x700))
    };
}
#endif
