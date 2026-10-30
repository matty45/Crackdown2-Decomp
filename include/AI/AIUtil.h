// AI utility functions (RuffKing: AI/Utility/AIUtil). RetGameTime is out of line in RuffKing (0x8246F690); CD2 inlines
// it (cAiPlayer::ShouldTriggerFootStepEvent 0x823EB518 loads the timer directly) and keeps one copy for the AILib
// script function "RetGameTime" (0x823E0CE0).
#ifndef AI_AIUTIL_H
#define AI_AIUTIL_H

#include "GMan/cGameManager.h"

namespace AI
{
    inline float RetGameTime() { return GMan::cGameManager::ms_fGameTimerSecs; }
}

#endif // AI_AIUTIL_H
