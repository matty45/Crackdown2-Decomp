#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPivotBasedProp.h"
#include <new>
#include "rws/classfactory.h"
// src/Prop/Constrained/cSpinningProp.cpp
//
// Class: cSpinningProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSpinningProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cSpinningProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cSpinningProp.cpp

#include "Prop/cSpinningProp.h"

namespace Prop
{
    RWS::CAttributeHandler *cSpinningProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSpinningPropPrototype(packet);
    }

    const char *cSpinningProp::RetClassName() const
    {
        return "cSpinningProp";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cSpinningProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpinningPropClass = new Fun_Runtime::cClass(0x101C, "cSpinningProp", 0xE50);
        return *cSpinningPropClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cSpinningProp::ms_pcSpinningPropClass = &cSpinningProp::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cSpinningPropRegistrar(
        "cSpinningProp", cSpinningProp::MakeNew, 0xE50, false);
}

namespace Prop
{
    RWS::CAttributeHandler *cSpinningProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cSpinningProp(prototype);
        return 0;
    }
}

// CD2 0x82FF8EF0: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cSpinningPropcPivotBasedPropInheritRegistrar(
        Prop::cSpinningProp::StaticCreateClass(), Prop::cPivotBasedProp::StaticCreateClass());
}
