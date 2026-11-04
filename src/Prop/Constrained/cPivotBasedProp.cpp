#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
// src/Prop/Constrained/cPivotBasedProp.cpp
//
// Class: cPivotBasedProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPivotBasedProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cPivotBasedProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cPivotBasedProp.cpp

#include "Prop/cPivotBasedProp.h"
#include <new>

namespace Prop
{
    RWS::CAttributeHandler *cPivotBasedProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPivotBasedPropPrototype(packet);
    }

    const char *cPivotBasedProp::RetClassName() const
    {
        return "cPivotBasedProp";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cPivotBasedProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPivotBasedPropClass = new Fun_Runtime::cClass(0x895440, "cPivotBasedProp", 0xE40);
        return *cPivotBasedPropClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cPivotBasedProp::ms_pcPivotBasedPropClass = &cPivotBasedProp::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cPivotBasedPropRegistrar(
        "cPivotBasedProp", cPivotBasedProp::MakeNew, 0xE40, false);
}

namespace Prop
{
    RWS::CAttributeHandler *cPivotBasedProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cPivotBasedProp(prototype);
        return 0;
    }
}

// CD2 0x82FF7D30: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cPivotBasedPropcPropInheritRegistrar(
        Prop::cPivotBasedProp::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

#include "gom/proto_registrar.h"

// CD2 0x82FF7DE8: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace Prop
{
    static GOM::cProtoRegistrar cPivotBasedPropSpawningRegistrar(
        cPivotBasedProp::StaticCreateClass(), cPivotBasedProp::SpawnFromPrototype);
}
