// STAND-IN: descriptive prototype name is ours; CD2 MakeNew at 0x8253ED68 allocates 0x460, calls
// cCwTransCharacterPrototype (0x82312E00) and installs table 0x82007C00: the constructor is inline and adds no fields.
// Slot 5 is CAttributeHandler::Init at 0x8253EF10.
#ifndef CHARACTER_CCWTRANSCHARACTERWRAPPERPROTOTYPE_H
#define CHARACTER_CCWTRANSCHARACTERWRAPPERPROTOTYPE_H
#include "CHARACTER/cCwTransCharacter.h"
namespace CHARACTER
{
    class cCwTransCharacterWrapperPrototype : public cCwTransCharacter::cCwTransCharacterPrototype
    {
    public:
        __forceinline cCwTransCharacterWrapperPrototype(const RWS::CAttributePacket &packet)
            : cCwTransCharacter::cCwTransCharacterPrototype(packet) {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(cCwTransCharacterWrapperPrototype,
            CD2_SIZE(cCwTransCharacterWrapperPrototype, 0x460))
    };
}
#endif
