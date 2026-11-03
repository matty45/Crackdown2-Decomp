// STAND-IN: RuffKing NPCArmedBehaviour derives from NPCBehaviour. CD2's
// StaticCreateClass (0x824A7E80) gives size 0xF0; fields after the 0xC0 base are unmodelled.
#ifndef AI_NPCARMEDBEHAVIOUR_H
#define AI_NPCARMEDBEHAVIOUR_H
#include "AI/NPCBehaviour.h"
namespace AI
{
    class NPCArmedBehaviour : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelledC0[0xF0 - 0xC0];
        CD2_LAYOUT_CHECKS(NPCArmedBehaviour, CD2_SIZE(NPCArmedBehaviour, 0xF0))
    };
}
#endif
