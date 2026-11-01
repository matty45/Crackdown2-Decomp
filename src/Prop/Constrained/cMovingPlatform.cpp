#include "rws/classfactory.h"
// src/Prop/Constrained/cMovingPlatform.cpp
//
// Class: cMovingPlatform (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cMovingPlatform.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cMovingPlatform.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cMovingPlatform.cpp

#include "Prop/cMovingPlatform.h"

namespace Prop
{
    const char *cMovingPlatform::RetClassName() const
    {
        return "cMovingPlatform";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cMovingPlatform::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMovingPlatformClass = new Fun_Runtime::cClass(0x1020, "cMovingPlatform", 0xE40);
        return *cMovingPlatformClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cMovingPlatform::ms_pcMovingPlatformClass = &cMovingPlatform::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cMovingPlatformRegistrar(
        "cMovingPlatform", cMovingPlatform::MakeNew, 0xE40, false);
}
