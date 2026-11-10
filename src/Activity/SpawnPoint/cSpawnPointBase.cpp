// Activity/SpawnPoint/cSpawnPointBase.cpp: RuffKing's Libraries/Shared/ActivityManager/SpawnPoint/cSpawnPointBase.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "Activity/cSpawnPointBase.h"
#include "cd2/memory.h"
#include "gom/manager.h"
#include "rws/systemcommands.h"
#include "fun_runtime/mtx.h"

namespace Activity
{
    unsigned int cSpawnPointBase::ms_nNextUID = 1000;

    Fun_Runtime::cClass &cSpawnPointBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpawnPointBaseClass = new Fun_Runtime::cClass(0x5D1F2, "cSpawnPointBase", 0x50);
        return *cSpawnPointBaseClass;
    }

    void cSpawnPointBase::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, "cSpawnPointBase"); !it.IsFinished(); ++it)
        {
            if (it->GetCommandId() == 0)
            {
                const RWS::RWSGUID guid = it->GetAs_RWSGUID();
                m_pPrototype = GOM::FindPrototypeById(guid);
            }
        }
        HandleSystemCommands(packet);
    }

    void cSpawnPointBase::HandleSystemCommands(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, RWS::CSystemCommands::pCSystemCommandsClassID);
             !it.IsFinished(); ++it)
        {
            if (it->GetCommandId() == RWS::CSystemCommands::CMD_LoadMatrix)
            {
                SetTransform(it->GetAs_Mtx());
                return;
            }
        }
    }

    const Fun_Runtime::cClass *cSpawnPointBase::ms_pcSpawnPointBaseClass = &cSpawnPointBase::StaticCreateClass();
}
