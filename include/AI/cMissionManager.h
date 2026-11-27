// AI::cMissionManager (Crackdown 2): STAND-IN for its mission vectors. RuffKing's bases (cLoadSaveObject and
// cDebugPageHandler, one vptr each) are followed in CD2 by the mission vector at +8: cAmbientEventMission::RetMissionID
// (0x8248DD70) reads its begin and end at +0xC/+0x10 where RuffKing's reads m_vMissions (+0x30 there, after debug
// fields CD2 does not have). RuffKing's m_vAmbientMissions follows it (+0x40 there, +0x18 in CD2: the expanded
// RegisterAmbientEventMission in cAmbientEventMission::HandleAttributes, 0x8248DFC0, pushes onto +0x18 and reads
// +0x1C/+0x20). The rest of the manager is not modelled.
#ifndef AI_CMISSIONMANAGER_H
#define AI_CMISSIONMANAGER_H

#include "cd2/layout.h"
#include "fun_runtime/vector.h"
#include "GDb/cDebugPageHandler.h"
#include "SaveGame/cLoadSaveObject.h"
#include "AI/cAmbientEventMission.h"

namespace AI
{
    class cMissionBase;

    class cMissionManager : public SaveGame::cLoadSaveObject, public GDb::cDebugPageHandler
    {
    public:
        // RuffKing's name; CD2 0x838009CC.
        static cMissionManager *ms_pMissionManager;
        // RuffKing's (out of line there, 0x823F2C50, with a debug assert that the ID fits a byte); CD2 has no copy:
        // cAmbientEventMission::HandleAttributes (0x8248DFC0) expands it.
        unsigned short RegisterAmbientEventMission(cAmbientEventMission *pMission)
        {
            m_vAmbientMissions.push_back(pMission);
            return m_vAmbientMissions.size() - 1;
        }
        Fun_Runtime::cVector<cMissionBase *> m_vMissions;
    private:
        Fun_Runtime::cVector<cMissionBase *> m_vAmbientMissions;

        CD2_LAYOUT_CHECKS(cMissionManager,
            CD2_OFFSET(cMissionManager, m_vMissions, 8)
            CD2_OFFSET(cMissionManager, m_vAmbientMissions, 0x18))
    };
}

#endif // AI_CMISSIONMANAGER_H
