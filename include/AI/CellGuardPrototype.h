// AI::CellGuardPrototype (Crackdown 2): STAND-IN. RuffKing declares it in its own header, AI::CellGuardPrototype :
// NPCBehaviourPrototype, 256 bytes. CD2's CellGuard::MakeNew (0x824C0B08) allocates 0x100 and calls this constructor
// (0x824C5E78), which calls NPCBehaviourPrototype's (0x824A8608). The prototype's own fields are not recovered.
#ifndef AI_CELLGUARDPROTOTYPE_H
#define AI_CELLGUARDPROTOTYPE_H

#include "AI/cChaseBehaviour.h"
#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class CellGuardPrototype : public NPCBehaviourPrototype
    {
    public:
        CellGuardPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled90[0x100 - 0x90];

        CD2_LAYOUT_CHECKS(CellGuardPrototype,
            CD2_SIZE(CellGuardPrototype, 0x100))
    };
}

#endif // AI_CELLGUARDPROTOTYPE_H
