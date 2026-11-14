// AI::cGameDirectionManager (Crackdown 2): STAND-IN for the singleton and the one method a matched function uses; the
// class layout is not modelled. RuffKing's cCellStrongholdMission::TickUpdate passes the mission to
// cGameDirectionManager::SetCurrentCSMission when the local player is inside its containment zone and
// ms_pGameDirectionManager is set; CD2's (0x824750A0) reads the singleton at 0x838009D4 and calls 0x824A1E78.
#ifndef AI_CGAMEDIRECTIONMANAGER_H
#define AI_CGAMEDIRECTIONMANAGER_H

namespace AI
{
    class cCellStrongholdMission;

    class cGameDirectionManager
    {
    public:
        static cGameDirectionManager *ms_pGameDirectionManager;
        void SetCurrentCSMission(cCellStrongholdMission *pMission);
    };
}

#endif // AI_CGAMEDIRECTIONMANAGER_H
