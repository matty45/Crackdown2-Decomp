#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
// The shared cProp hierarchy now reproduces the inherited vptr stores exactly.
#include <new>
#include "rws/classfactory.h"
// src/Prop/Constrained/cMovingPlatform.cpp
//
// Class: cMovingPlatform (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cMovingPlatform.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Constrained/cMovingPlatform.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Constrained/cMovingPlatform.cpp

#include "Prop/cMovingPlatform.h"

namespace Prop
{
    // The derived class has no cleanup; cProp's missing secondary bases still prevent
    // the destructor body from matching, independently of its deleting wrapper.
    cMovingPlatform::~cMovingPlatform()
    {
    }

    const char *cMovingPlatform::RetClassName() const
    {
        return "cMovingPlatform";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cMovingPlatform::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMovingPlatformClass = new Fun_Runtime::cClass(0x1020, "cMovingPlatform", 0xE40);
        return *cMovingPlatformClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cMovingPlatform::ms_pcMovingPlatformClass = &cMovingPlatform::StaticCreateClass();
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cMovingPlatformRegistrar(
        "cMovingPlatform", cMovingPlatform::MakeNew, 0xE40, false);
}

namespace Prop
{
    RWS::CAttributeHandler *cMovingPlatform::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cMovingPlatform(prototype);
        return 0;
    }
}

// CD2 0x82FF7A50: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cMovingPlatformcPropInheritRegistrar(
        Prop::cMovingPlatform::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

#include "gom/proto_registrar.h"

// CD2 0x82FF7B08: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace Prop
{
    static GOM::cProtoRegistrar cMovingPlatformSpawningRegistrar(
        cMovingPlatform::StaticCreateClass(), cMovingPlatform::SpawnFromPrototype);
}
