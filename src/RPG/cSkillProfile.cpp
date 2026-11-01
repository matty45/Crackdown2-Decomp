// src/RPG/cSkillProfile.cpp
//
// Class: cSkillProfile (namespace: RPG). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSkillProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/RPG/cSkillProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/RPG/cSkillProfile.cpp

#include "RPG/cSkillProfile.h"

namespace RPG
{
    const char *cSkillProfile::RetClassName() const
    {
        return "cSkillProfile";
    }
}

#include "cd2/memory.h"

namespace RPG
{
    Fun_Runtime::cClass &cSkillProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSkillProfileClass = new Fun_Runtime::cClass(0x609, "cSkillProfile", 0x5A8);
        return *cSkillProfileClass;
    }
}

namespace RPG
{
    const Fun_Runtime::cClass *cSkillProfile::ms_pcSkillProfileClass = &cSkillProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cSkillProfile::RetClass() const
    {
        return *ms_pcSkillProfileClass;
    }
}

namespace RPG
{
    bool cSkillProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSkillProfileClass->IsA(c);
    }
}
