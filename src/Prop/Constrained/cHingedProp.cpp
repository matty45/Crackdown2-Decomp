#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPivotBasedProp.h"
#include "rws/classfactory.h"
// src/Prop/Constrained/cHingedProp.cpp
//
// Class: cHingedProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cHingedProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cHingedProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cHingedProp.cpp

#include "Prop/cHingedProp.h"
#include <new>

namespace Prop
{
    RWS::CAttributeHandler *cHingedProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHingedPropPrototype(packet);
    }

    const char *cHingedProp::RetClassName() const
    {
        return "cHingedProp";
    }

    // CD2 0x82737698 has no derived cleanup beyond vtable restoration.
    cHingedProp::~cHingedProp()
    {
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cHingedProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedPropClass = new Fun_Runtime::cClass(0x101D, "cHingedProp", 0xEB0);
        return *cHingedPropClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cHingedProp::ms_pcHingedPropClass = &cHingedProp::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cHingedPropRegistrar(
        "cHingedProp", cHingedProp::MakeNew, 0xEB0, false);
}

namespace Prop
{
    RWS::CAttributeHandler *cHingedProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cHingedProp(prototype);
        return 0;
    }
}

// CD2 0x82FF70D0: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cHingedPropcPivotBasedPropInheritRegistrar(
        Prop::cHingedProp::StaticCreateClass(), Prop::cPivotBasedProp::StaticCreateClass());
}

// CD2 0x82FF7188: register the class descriptor and placement factory.
namespace Prop
{
    static GOM::cProtoRegistrar cHingedPropSpawningRegistrar(
        cHingedProp::StaticCreateClass(), cHingedProp::SpawnFromPrototype);
}

#include "Prop/cHingedProp.h"
#include "fun_runtime/script_type_registrar.h"

namespace Prop
{
    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHingedProp> cHingedPropScriptRegistrar(
        "cHingedProp", "cProp");
}

namespace Prop
{
    const Fun_Runtime::cScriptTypeRegistration *cHingedProp::RetScriptTypeRegistration() const
    {
        return &cHingedPropScriptRegistrar;
    }
}
