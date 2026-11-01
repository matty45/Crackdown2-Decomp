// AI::AIBehaviour (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x824A4A80) is slot 11 of the vtable at 0x82107B90, as cNonGameBase's RetClassName.
#ifndef AI_AIBEHAVIOUR_H
#define AI_AIBEHAVIOUR_H

#include "gom/non_game_base.h"

namespace AI
{
    class AIBehaviour : public cNonGameBase
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif // AI_AIBEHAVIOUR_H
