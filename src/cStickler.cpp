#include "Equip/cCWSatchelCharge.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
// src/cStickler.cpp
//
// Class: cStickler (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cStickler.cpp

#include "unknown/cStickler.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cStickler::ms_pcSticklerClass = &cStickler::StaticCreateClass();

    Fun_Runtime::cClass &cStickler::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSticklerClass = new Fun_Runtime::cClass(0x10142, "cStickler", 0xAE0);
        return *cSticklerClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cSticklerRegistrar(
        "cStickler", cStickler::MakeNew, 0xAE0, false);
}

// CD2 0x82FD10A8: register the class descriptor and placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cSticklerSpawningRegistrar(
        cStickler::StaticCreateClass(), cStickler::SpawnFromPrototype);
}

// CD2 0x82FD0FF0: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cSticklercCWSatchelChargeInheritRegistrar(
        unknown::cStickler::StaticCreateClass(), Equip::cCWSatchelCharge::StaticCreateClass());
}

namespace unknown
{
    const char *cStickler::RetClassName() const
    {
        return "cStickler";
    }
}

#include "unknown/cSticklerPrototype.h"

namespace unknown
{
    Fun_Runtime::RetVal cSticklerPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
