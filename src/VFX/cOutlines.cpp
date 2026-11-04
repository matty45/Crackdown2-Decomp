#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/VFX/cOutlines.cpp
//
// Class: cOutlines (namespace: VFX). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cOutlines.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cOutlines.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cOutlines.cpp

#include "VFX/cOutlines.h"

namespace VFX
{
    const char *cOutlines::RetClassName() const
    {
        return "cOutlines";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cOutlines::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cOutlinesClass = new Fun_Runtime::cClass(0x1027FA, "cOutlines", 0x460);
        return *cOutlinesClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cOutlines::ms_pcOutlinesClass = &cOutlines::StaticCreateClass();
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cOutlinesRegistrar(
        "cOutlines", cOutlines::MakeNew, 0x460, false);
}

// CD2 0x83007820: runtime class inheritance registration.
namespace VFX
{
    static Fun_Runtime::cInheritanceRegistrar cOutlinescNonGameBaseInheritRegistrar(
        VFX::cOutlines::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x827A0B98: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cOutlines::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cOutlines;
    }
}
