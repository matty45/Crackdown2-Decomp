#include "rws/classfactory.h"
// src/Prop/Constrained/cPivotBasedProp.cpp
//
// Class: cPivotBasedProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPivotBasedProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cPivotBasedProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cPivotBasedProp.cpp

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    const char *cPivotBasedProp::RetClassName() const
    {
        return "cPivotBasedProp";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cPivotBasedProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPivotBasedPropClass = new Fun_Runtime::cClass(0x895440, "cPivotBasedProp", 0xE40);
        return *cPivotBasedPropClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cPivotBasedProp::ms_pcPivotBasedPropClass = &cPivotBasedProp::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cPivotBasedPropRegistrar(
        "cPivotBasedProp", cPivotBasedProp::MakeNew, 0xE40, false);
}
