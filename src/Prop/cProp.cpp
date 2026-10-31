// src/Prop/cProp.cpp
//
// Class: cProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is cProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/cProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/cProp.cpp

#include "Prop/cProp.h"
#include "rws/classfactory.h"

namespace Prop
{
    // CD2 0x82FF5298 registers the prototype factory 0x82729378 for a 0xE30-byte cProp.
    static RWS::CClassFactory::CRegistrar cPropRegistrar(
        "cProp", cProp::MakeNew, 0xE30, false);
}
