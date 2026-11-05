#include "rws/classfactory.h"
#include "GameManagement/cGameModeSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    void cGameModeSpawnPoint::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, RWS::CSystemCommands::pCSystemCommandsClassID);
             !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case RWS::CSystemCommands::CMD_LoadMatrix:
                m_Transform = it->GetAs_Mtx();
                break;
            }
        }
    }

    RWS::CAttributeHandler *cGameModeSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeSpawnPoint;
    }

    const char *cGameModeSpawnPoint::RetClassName() const
    {
        return "cGameModeSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cGameModeSpawnPointRegistrar(
        "cGameModeSpawnPoint", cGameModeSpawnPoint::MakeNew, 0x60, false);
}
