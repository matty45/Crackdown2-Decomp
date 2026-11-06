// AI::CellRocketPrototype (Crackdown 2): STAND-IN. RuffKing declares it in its own header, AI::CellRocketPrototype :
// NPCBehaviourPrototype, 240 bytes. CD2's CellRocket::MakeNew (0x824C3D80) allocates 0xF0 and calls this constructor
// (0x823B8880), which calls NPCBehaviourPrototype's (0x824A8608). The prototype's own fields are not recovered.
#ifndef AI_CELLROCKETPROTOTYPE_H
#define AI_CELLROCKETPROTOTYPE_H

#include "AI/cChaseBehaviour.h"
#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class CellRocketPrototype : public NPCBehaviourPrototype
    {
    public:
        CellRocketPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled90[0xF0 - 0x90];

        CD2_LAYOUT_CHECKS(CellRocketPrototype,
            CD2_SIZE(CellRocketPrototype, 0xF0))
    };
}

#endif // AI_CELLROCKETPROTOTYPE_H
