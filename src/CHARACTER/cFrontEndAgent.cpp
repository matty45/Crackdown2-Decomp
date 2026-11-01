// src/CHARACTER/cFrontEndAgent.cpp
//
// Class: cFrontEndAgent (namespace: CHARACTER). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is FrontEndAgent.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/UI/Screens/FrontEnd/FrontEndAgent.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CHARACTER/cFrontEndAgent.cpp

#include "CHARACTER/cFrontEndAgent.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const Fun_Runtime::cClass *cFrontEndAgent::ms_pcFrontEndAgentClass = &cFrontEndAgent::StaticCreateClass();

    Fun_Runtime::cClass &cFrontEndAgent::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFrontEndAgentClass = new Fun_Runtime::cClass(0x67D, "cFrontEndAgent", 0x3EC0);
        return *cFrontEndAgentClass;
    }
}
