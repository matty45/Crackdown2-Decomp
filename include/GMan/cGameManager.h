// GMan::cGameManager (Crackdown 2): STAND-IN for its game timer only. RuffKing's AI::RetGameTime (0x8246F690) returns
// GMan::cGameManager::ms_fGameTimerSecs; CD2's AILib script function "RetGameTime" (0x823E0CE0, registered at
// 0x82F5FBD4) returns the float at 0x8383A974, which cAiPlayer's sound-event checks read inline.
#ifndef GMAN_CGAMEMANAGER_H
#define GMAN_CGAMEMANAGER_H

#include "rws/eventid.h"

// RuffKing's cGameManager.cpp defines this message at global scope; CD2's copy is at 0x8383A95C, which
// cTrainingMission::OnMissionUnlocked (0x82480DA0) links with the format "Mtx *".
extern RWS::CEventId iMsgRestartPlayer;
// RuffKing's cGameManager.cpp defines this one at global scope too. RuffKing's cTimeOfDay destructor unlinks
// iMsgRunningTick and then iMsgBeginPlay; CD2's (0x82774280) unlinks 0x83A05C54 and then 0x8383A94C.
extern RWS::CEventId iMsgBeginPlay;

namespace GMan
{
    class cGameManager
    {
    public:
        // RuffKing ForceCharacterH2HContact names this counter; CD2's corresponding methods read 0x8383A96C.
        static unsigned int ms_nGameTicks;
        static float ms_fGameTimerSecs;
    };
}

#endif // GMAN_CGAMEMANAGER_H
