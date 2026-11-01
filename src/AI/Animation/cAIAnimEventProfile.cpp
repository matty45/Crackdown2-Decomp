// src/AI/Animation/cAIAnimEventProfile.cpp
//
// Class: cAIAnimEventProfile (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cAIAnimEventProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Animation/cAIAnimEventProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Animation/cAIAnimEventProfile.cpp

#include "AI/cAIAnimEventProfile.h"

namespace AI
{
    const char *cAIAnimEventProfile::RetClassName() const
    {
        return "cAIAnimEventProfile";
    }
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAIAnimEventProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAIAnimEventProfileClass = new Fun_Runtime::cClass(0x9FCE4, "cAIAnimEventProfile", 0x4C);
        return *cAIAnimEventProfileClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cAIAnimEventProfile::ms_pcAIAnimEventProfileClass = &cAIAnimEventProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cAIAnimEventProfile::RetClass() const
    {
        return *ms_pcAIAnimEventProfileClass;
    }
}

namespace AI
{
    bool cAIAnimEventProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAIAnimEventProfileClass->IsA(c);
    }
}
