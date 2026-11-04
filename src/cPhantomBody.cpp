#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
// src/cPhantomBody.cpp
//
// Class: cPhantomBody (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cPhantomBody.cpp

#include "unknown/cPhantomBody.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cPhantomBody::ms_pcPhantomBodyClass = &cPhantomBody::StaticCreateClass();

    Fun_Runtime::cClass &cPhantomBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPhantomBodyClass = new Fun_Runtime::cClass(0x7, "cPhantomBody", 0x140);
        return *cPhantomBodyClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cPhantomBodyRegistrar(
        "cPhantomBody", cPhantomBody::MakeNew, 0x140, false);
}

// CD2 0x82FE0060: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cPhantomBodycGameBaseInheritRegistrar(
        unknown::cPhantomBody::StaticCreateClass(), cGameBase::StaticCreateClass());
}

#include <new>

// CD2 0x8268A3F0: placement factory; the constructor stays out of line (a tail call).
namespace unknown
{
    RWS::CAttributeHandler *cPhantomBody::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPhantomBody;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FE0118: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cPhantomBodySpawningRegistrar(
        cPhantomBody::StaticCreateClass(), cPhantomBody::SpawnFromPrototype);
}

// CD2 0x8268A2F8.
namespace unknown
{
    const Fun_Runtime::cClass &cPhantomBody::RetClass() const
    {
        return *ms_pcPhantomBodyClass;
    }
}

// CD2 0x8268A3E0.
namespace unknown
{
    const char *cPhantomBody::RetClassName() const
    {
        return "cPhantomBody";
    }
}
