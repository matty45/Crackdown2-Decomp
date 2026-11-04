#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/VFX/cGlobalLightManager.cpp
//
// Class: cGlobalLightManager (namespace: VFX). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cGlobalLightManager.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cGlobalLightManager.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cGlobalLightManager.cpp

#include "VFX/cGlobalLightManager.h"

namespace VFX
{
    const char *cGlobalLightManager::RetClassName() const
    {
        return "cGlobalLightManager";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cGlobalLightManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGlobalLightManagerClass = new Fun_Runtime::cClass(0x1F97F, "cGlobalLightManager", 0x5AE0);
        return *cGlobalLightManagerClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cGlobalLightManager::ms_pcGlobalLightManagerClass = &cGlobalLightManager::StaticCreateClass();
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cGlobalLightManagerRegistrar(
        "cGlobalLightManager", cGlobalLightManager::MakeNew, 0x5AE0, false);
}

// CD2 0x8300B498: runtime class inheritance registration.
namespace VFX
{
    static Fun_Runtime::cInheritanceRegistrar cGlobalLightManagercNonGameBaseInheritRegistrar(
        VFX::cGlobalLightManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x827FAFE0: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cGlobalLightManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGlobalLightManager;
    }
}
