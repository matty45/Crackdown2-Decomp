#include "rws/classfactory.h"
// src/VFX/cBloom.cpp
//
// Class: cBloom (namespace: VFX). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is cBloom.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cBloom.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cBloom.cpp

#include "VFX/cBloom.h"

namespace VFX
{
    const char *cBloom::RetClassName() const
    {
        return "cBloom";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cBloomRegistrar(
        "cBloom", cBloom::MakeNew, 0x80, false);
}

namespace VFX
{
    const Fun_Runtime::cClass &cBloom::RetClass() const
    {
        return *ms_pccBloomClass;
    }
}
