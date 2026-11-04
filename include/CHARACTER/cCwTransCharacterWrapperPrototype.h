// STAND-IN: descriptive prototype name is ours; CD2 MakeNew at 0x8253ED68
// calls cCwTransCharacterPrototype (0x82312E00) and installs table 0x82007C00.
// Slot 5 is CAttributeHandler::Init at 0x8253EF10. Interface only; storage is unrecovered.
#ifndef CHARACTER_CCWTRANSCHARACTERWRAPPERPROTOTYPE_H
#define CHARACTER_CCWTRANSCHARACTERWRAPPERPROTOTYPE_H
#include "CHARACTER/cCwTransCharacter.h"
namespace CHARACTER
{
    class cCwTransCharacterWrapperPrototype : public cCwTransCharacter::cCwTransCharacterPrototype
    {
    public:
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    };
}
#endif
