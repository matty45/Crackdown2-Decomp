#include "rws/classfactory.h"
// src/Prop/Custom/cGasCanister.cpp
//
// Class: cGasCanister (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cGasCanister.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cGasCanister.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cGasCanister.cpp

#include "Prop/cGasCanister.h"

namespace Prop
{
    const char *cGasCanister::RetClassName() const
    {
        return "cGasCanister";
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cGasCanisterRegistrar(
        "cGasCanister", cGasCanister::MakeNew, 0xe40, false);
}
