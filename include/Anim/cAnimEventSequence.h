// STAND-IN: Burn's event-list names/layout, embedded in its 16-byte cAnimData.
#ifndef ANIM_CANIMEVENTSEQUENCE_H
#define ANIM_CANIMEVENTSEQUENCE_H
#include "cd2/layout.h"
namespace Anim
{
    class cAnimEvent;
    class cAnimEventSequence
    {
    public:
        cAnimEventSequence();
        cAnimEvent *pEvents;
        unsigned char nNumEvents;
        CD2_LAYOUT_CHECKS(cAnimEventSequence,
            CD2_SIZE(cAnimEventSequence, 8)
            CD2_OFFSET(cAnimEventSequence, pEvents, 0)
            CD2_OFFSET(cAnimEventSequence, nNumEvents, 4))
    };
}
#endif
