// GameManagement::cGameModeCheckpoint: class-factory and virtual-table markers in CD2;
// the reference cGameModeCheckpoint.cpp names this source object.
#include "GameManagement/cGameModeCheckpoint.h"
#include "rws/classfactory.h"
#include "GameManagement/cGameModeArena.h"
#include "GameManagement/cGameModeStartZone.h"
namespace GameManagement
{
    const char *cGameModeCheckpoint::RetClassName() const
    {
        return "cGameModeCheckpoint";
    }

    void cGameModeCheckpoint::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cGameModeTriggerZone::HandleAttributes(packet);
        if (packet.IsInstanceCreationPacket())
        {
            cGameModeArena *arena = cArenaLinker::GetArena(m_sArenaName);
            if (arena)
                arena->AddCheckpoint(this);
        }
    }

    cGameModePrototype *cGameModeCheckpoint::RetGameModePrototype() const
    {
        if (cArenaLinker::GetArena(m_sArenaName))
            return RetStartZone()->RetGameModePrototype();
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cGameModeCheckpointRegistrar(
        "cGameModeCheckpoint", cGameModeCheckpoint::MakeNew, 0x1C0, false);
}
