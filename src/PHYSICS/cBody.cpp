#include "PHYSICS/cDynamicBody.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
// src/PHYSICS/cBody.cpp
//
// Class: cBody (namespace: PHYSICS). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cBody.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Physics/cBody.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PHYSICS/cBody.cpp

#include "PHYSICS/cBody.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    const Fun_Runtime::cClass *cBody::ms_pcBodyClass = &cBody::StaticCreateClass();

    Fun_Runtime::cClass &cBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBodyClass = new Fun_Runtime::cClass(0x63C, "cBody", 0x250);
        return *cBodyClass;
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cBodyRegistrar(
        "cBody", cBody::MakeNew, 0x250, false);
}

// CD2 0x82FDF610: runtime class inheritance registration.
namespace PHYSICS
{
    static Fun_Runtime::cInheritanceRegistrar cBodycGameBaseInheritRegistrar(
        PHYSICS::cBody::StaticCreateClass(), cGameBase::StaticCreateClass());
}

// CD2 0x82FDF678: runtime class inheritance registration.
namespace PHYSICS
{
    static Fun_Runtime::cInheritanceRegistrar cBodycDebugPageHandlerInheritRegistrar(
        PHYSICS::cBody::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}

// CD2 0x82FDFB08: runtime class inheritance registration.
namespace PHYSICS
{
    static Fun_Runtime::cInheritanceRegistrar cDynamicBodycBodyInheritRegistrar(
        PHYSICS::cDynamicBody::StaticCreateClass(), PHYSICS::cBody::StaticCreateClass());
}
