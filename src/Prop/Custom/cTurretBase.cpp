// src/Prop/Custom/cTurretBase.cpp
//
// Class: cTurretBase (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cTurretBase.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cTurretBase.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cTurretBase.cpp

#include "Prop/cTurretBase.h"

namespace Prop
{
    const char *cTurretBase::RetClassName() const
    {
        return "cTurretBase";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cTurretBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTurretBaseClass = new Fun_Runtime::cClass(0x1027, "cTurretBase", 0x1080);
        return *cTurretBaseClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cTurretBase::ms_pcTurretBaseClass = &cTurretBase::StaticCreateClass();

    const Fun_Runtime::cClass &cTurretBase::RetClass() const
    {
        return *ms_pcTurretBaseClass;
    }
}

namespace Prop
{
    bool cTurretBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTurretBaseClass->IsA(c);
    }
}
