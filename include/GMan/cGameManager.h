// GMan::cGameManager (Crackdown 2): STAND-IN for its game timer only. RuffKing's AI::RetGameTime (0x8246F690) returns
// GMan::cGameManager::ms_fGameTimerSecs; CD2's AILib script function "RetGameTime" (0x823E0CE0, registered at
// 0x82F5FBD4) returns the float at 0x8383A974, which cAiPlayer's sound-event checks read inline.
#ifndef GMAN_CGAMEMANAGER_H
#define GMAN_CGAMEMANAGER_H

namespace GMan
{
    class cGameManager
    {
    public:
        static float ms_fGameTimerSecs;
    };
}

#endif // GMAN_CGAMEMANAGER_H
