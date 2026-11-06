// src/WorldManager/cStaticEnvironment.cpp
//
// Class: cStaticEnvironment (namespace: WorldManager). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cStaticEnvironment1.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/WorldManager/cStaticEnvironment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/WorldManager/cStaticEnvironment.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cStaticBody.h"
#include "rws/classfactory.h"
#include "WorldManager/cStaticEnvironment.h"
#include "cd2/memory.h"

namespace WorldManager
{
    const Fun_Runtime::cClass *cStaticEnvironment::ms_pcStaticEnvironmentClass = &cStaticEnvironment::StaticCreateClass();

    Fun_Runtime::cClass &cStaticEnvironment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStaticEnvironmentClass = new Fun_Runtime::cClass(0x3, "cStaticEnvironment", 0x2E0);
        return *cStaticEnvironmentClass;
    }

    static RWS::CClassFactory::CRegistrar cStaticEnvironmentRegistrar(
        "cStaticEnvironment", cStaticEnvironment::MakeNew, 0x2E0, false);

    // CD2 0x8300CB78: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cStaticEnvironmentcStaticBodyInheritRegistrar(
        WorldManager::cStaticEnvironment::StaticCreateClass(), PHYSICS::cStaticBody::StaticCreateClass());

    const char *cStaticEnvironment::RetClassName() const
    {
        return "cStaticEnvironment";
    }
}
