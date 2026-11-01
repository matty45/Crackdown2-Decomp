// src/AI/cBeaconProp.cpp
//
// Class: cBeaconProp (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is BeaconProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/AU/BeaconProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/cBeaconProp.cpp

#include "AI/cBeaconProp.h"

namespace AI
{
    const char *cBeaconProp::RetClassName() const
    {
        return "cBeaconProp";
    }
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cBeaconProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBeaconPropClass = new Fun_Runtime::cClass(0x4172, "cBeaconProp", 0xE50);
        return *cBeaconPropClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cBeaconProp::ms_pcBeaconPropClass = &cBeaconProp::StaticCreateClass();

    const Fun_Runtime::cClass &cBeaconProp::RetClass() const
    {
        return *ms_pcBeaconPropClass;
    }
}

namespace AI
{
    bool cBeaconProp::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBeaconPropClass->IsA(c);
    }
}
