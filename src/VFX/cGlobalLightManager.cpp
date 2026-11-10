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

#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "VFX/cGlobalLightManager.h"
#include "cd2/memory.h"

namespace VFX
{
    void cGlobalLight::SetOccluded(bool bOccluded)
    {
        if (bOccluded)
        {
            if (!IsOccluded())
                cGlobalLightManager::ms_pSingleton->AddOccludedLight(this);
        }
        else if (IsOccluded())
            cGlobalLightManager::ms_pSingleton->RemoveOccludedLight(this);
    }

    const char *cGlobalLightManager::RetClassName() const
    {
        return "cGlobalLightManager";
    }

    Fun_Runtime::cClass &cGlobalLightManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cGlobalLightManagerClass = new Fun_Runtime::cClass(0x1F97F, "cGlobalLightManager", 0x5AE0);
        return *cGlobalLightManagerClass;
    }

    const Fun_Runtime::cClass *cGlobalLightManager::ms_pcGlobalLightManagerClass = &cGlobalLightManager::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cGlobalLightManagerRegistrar(
        "cGlobalLightManager", cGlobalLightManager::MakeNew, 0x5AE0, false);

    // CD2 0x8300B498: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cGlobalLightManagercNonGameBaseInheritRegistrar(
        VFX::cGlobalLightManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x827FAFE0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGlobalLightManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGlobalLightManager;
    }
}
