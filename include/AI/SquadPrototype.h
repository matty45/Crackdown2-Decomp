// AI::SquadPrototype (Crackdown 2): RuffKing declares it in its own header, AI::SquadPrototype :
// cNonGameBase::cNonGameBasePrototype, 112 bytes. CD2's Squad::MakeNew (0x824D81A0) allocates 0x70, calls
// GOM::cObjectPrototype's constructor (0x82654118) and stores this class's vptrs, so its constructor is inline.
#ifndef AI_SQUADPROTOTYPE_H
#define AI_SQUADPROTOTYPE_H

#include "gom/non_game_base.h"
#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class SquadPrototype : public cNonGameBase::cNonGameBasePrototype
    {
    public:
        __forceinline SquadPrototype(const RWS::CAttributePacket &packet)
            : cNonGameBase::cNonGameBasePrototype(packet) {}

        CD2_LAYOUT_CHECKS(SquadPrototype,
            CD2_SIZE(SquadPrototype, 0x70))
    };
}

#endif // AI_SQUADPROTOTYPE_H
