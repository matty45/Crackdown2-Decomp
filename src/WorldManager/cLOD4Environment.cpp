// src/WorldManager/cLOD4Environment.cpp
//
// Class: cLOD4Environment (namespace: WorldManager). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cLOD4Environment.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/WorldManager/cLOD4Environment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/WorldManager/cLOD4Environment.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
#include "WorldManager/cLOD4Environment.h"
#include "WorldManager/cStaticEnvironment.h"
#include "cd2/memory.h"

namespace WorldManager
{
    const Fun_Runtime::cClass *cLOD4Environment::ms_pcLOD4EnvironmentClass = &cLOD4Environment::StaticCreateClass();

    RWS::CAttributeHandler *cLOD4Environment::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLOD4Environment;
    }

    Fun_Runtime::cClass &cLOD4Environment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLOD4EnvironmentClass = new Fun_Runtime::cClass(0x199E, "cLOD4Environment", 0x2C0);
        return *cLOD4EnvironmentClass;
    }

    static RWS::CClassFactory::CRegistrar cLOD4EnvironmentRegistrar(
        "cLOD4Environment", cLOD4Environment::MakeNew, 0x2C0, false);

    // CD2 0x8300C8D0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cLOD4EnvironmentcGameBaseInheritRegistrar(
        WorldManager::cLOD4Environment::StaticCreateClass(), cGameBase::StaticCreateClass());

    const char *cLOD4Environment::RetClassName() const
    {
        return "cLOD4Environment";
    }

    const Fun_Runtime::cClass &cLOD4Environment::RetClass() const
    {
        return *ms_pcLOD4EnvironmentClass;
    }

    void cLOD4Environment::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cGameBase::HandleAttributes(packet);
        if (packet.IsInstanceCreationPacket())
            m_EventHandler.Register(this, packet.GetInstanceId());
    }

    bool cLOD4Environment::AnyLOD3Fading() const
    {
        for (const Fun_Runtime::cSafeDeletablePointer<cStaticEnvironment> *block = m_vpEnvBlocks.begin();
             block != m_vpEnvBlocks.end(); ++block)
        {
            const cStaticEnvironment *environment = *block;
            if (environment && (environment->RetFadeState() == eFS_FadeIn || environment->RetFadeState() == eFS_FadeOut))
                return true;
        }
        return false;
    }
}
