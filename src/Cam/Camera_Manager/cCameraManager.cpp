#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
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

#include "Cam/cCameraManager.h"
#include "cd2/memory.h"

namespace Cam
{
    const Fun_Runtime::cClass *cCameraManager::ms_pcCameraManagerClass = &cCameraManager::StaticCreateClass();

    Fun_Runtime::cClass &cCameraManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCameraManagerClass = new Fun_Runtime::cClass(0x622, "cCameraManager", 0x170);
        return *cCameraManagerClass;
    }
}

namespace Cam
{
    static RWS::CClassFactory::CRegistrar cCameraManagerRegistrar(
        "cCameraManager", cCameraManager::MakeNew, 0x170, false);
}

// CD2 0x82FAB060: runtime class inheritance registration.
namespace Cam
{
    static Fun_Runtime::cInheritanceRegistrar cCameraManagercNonGameBaseInheritRegistrar(
        Cam::cCameraManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}
