// STAND-IN: descriptive prototype name is ours; CD2 factory/constructor installs
// table 0x821345D4 after calling the shared base prototype constructor 0x826B7BE0.
// Slot 5 names the inherited CAttributeHandler::Init interface (0x826B2D20).
// Interface only: complete storage is unrecovered; do not use this declaration for allocation.
#ifndef CD2_UNKNOWN_CTRANSFORMINGTRUCKPROTOTYPE_H
#define CD2_UNKNOWN_CTRANSFORMINGTRUCKPROTOTYPE_H
#include "Vehicle/cCar.h"
namespace unknown
{
    class cTransformingTruckPrototype : public Vehicle::cCar::cCarPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
