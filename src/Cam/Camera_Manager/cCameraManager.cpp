// src/Cam/Camera_Manager/cCameraManager.cpp
//
// Class: cCameraManager (namespace: Cam). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Projects/Shared/CameraLib/Camera_Manager/cCameraManager.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Cam/Camera_Manager/cCameraManager.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "Cam/cCameraManager.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Cam
{
    bool cCameraManager::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcCameraManagerClass->IsA(testClass);
    }

    cCameraManager *cCameraManager::sm_pInstance;

    cCameraManager *cCameraManager::RetInstance()
    {
        return sm_pInstance;
    }

    const Fun_Runtime::cClass *cCameraManager::ms_pcCameraManagerClass = &cCameraManager::StaticCreateClass();

    Fun_Runtime::cClass &cCameraManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCameraManagerClass = new Fun_Runtime::cClass(0x622, "cCameraManager", 0x170);
        return *cCameraManagerClass;
    }

    static RWS::CClassFactory::CRegistrar cCameraManagerRegistrar(
        "cCameraManager", cCameraManager::MakeNew, 0x170, false);

    // CD2 0x82FAB060: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCameraManagercNonGameBaseInheritRegistrar(
        Cam::cCameraManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    const char *cCameraManager::RetClassName() const
    {
        return "cCameraManager";
    }

    const Fun_Runtime::cClass &cCameraManager::RetClass() const
    {
        return *ms_pcCameraManagerClass;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCameraManager> cCameraManagerScriptRegistrar(
        "CameraManager", "cNonGameBase");

    const Fun_Runtime::cScriptTypeRegistration *cCameraManager::RetScriptTypeRegistration() const
    {
        return &cCameraManagerScriptRegistrar;
    }

    RWS::CAttributeHandler *cCameraManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCameraManager;
    }
}
