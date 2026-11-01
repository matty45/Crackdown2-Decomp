// src/VFX/cVFXSurfaceProfile.cpp
//
// Class: cVFXSurfaceProfile (namespace: VFX). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cVFXSurfaceProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cVFXSurfaceProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cVFXSurfaceProfile.cpp

#include "VFX/cVFXSurfaceProfile.h"

namespace VFX
{
    const char *cVFXSurfaceProfile::RetClassName() const
    {
        return "cVFXSurfaceProfile";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cVFXSurfaceProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVFXSurfaceProfileClass = new Fun_Runtime::cClass(0x1564, "cVFXSurfaceProfile", 0x80);
        return *cVFXSurfaceProfileClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cVFXSurfaceProfile::ms_pcVFXSurfaceProfileClass = &cVFXSurfaceProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cVFXSurfaceProfile::RetClass() const
    {
        return *ms_pcVFXSurfaceProfileClass;
    }
}

namespace VFX
{
    bool cVFXSurfaceProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVFXSurfaceProfileClass->IsA(c);
    }
}
