#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "GameManagement/cGameModeCheckpoint.h"
#include "GameManagement/cCheckpointArena.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cCheckpointArena::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCheckpointArena;
    }

    const char *cCheckpointArena::RetClassName() const
    {
        return "cCheckpointArena";
    }

    cGameModeStartZone *cCheckpointArena::RetStartZone() const
    {
        return m_pStartTriggerZone;
    }

    unsigned int cCheckpointArena::RetNumCheckpoints() const
    {
        return m_vCheckpoints.size();
    }

    cGameModeCheckpoint *cCheckpointArena::RetCheckpoint(unsigned int index) const
    {
        if (index < m_vCheckpoints.size())
            return m_vCheckpoints[index];
        return 0;
    }

    void cCheckpointArena::OnShutDownLevel()
    {
        cGameModeArena::OnShutDownLevel();
        // CD2 inlines the standard-vector clear operation instead of calling cVector's out-of-line wrapper.
        m_vCheckpoints.MyBase::clear();
        m_pStartTriggerZone = 0;
    }

    void cCheckpointArena::AddStartZone(cGameModeStartZone *zone)
    {
        m_pStartTriggerZone = zone;
    }

    void cCheckpointArena::AddCheckpoint(cGameModeCheckpoint *checkpoint)
    {
        m_vCheckpoints.push_back(checkpoint);
        checkpoint->SetCheckpointID(m_vCheckpoints.size() - 1);
    }

    static RWS::CClassFactory::CRegistrar cCheckpointArenaRegistrar(
        "cCheckpointArena", cCheckpointArena::MakeNew, 0x120, false);
}
