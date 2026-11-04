#include "Equip/cGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
// src/cBoostPack.cpp
//
// Class: cBoostPack (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cBoostPack.cpp

#include "unknown/cBoostPack.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cBoostPack::ms_pcBoostPackClass = &cBoostPack::StaticCreateClass();

    Fun_Runtime::cClass &cBoostPack::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBoostPackClass = new Fun_Runtime::cClass(0x10141, "cBoostPack", 0x9D0);
        return *cBoostPackClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cBoostPackRegistrar(
        "cBoostPack", cBoostPack::MakeNew, 0x9D0, false);
}

// CD2 0x82FCC368: register the class descriptor and placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cBoostPackSpawningRegistrar(
        cBoostPack::StaticCreateClass(), cBoostPack::SpawnFromPrototype);
}

// CD2 0x82FCC2B0: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cBoostPackcGrenadeInheritRegistrar(
        unknown::cBoostPack::StaticCreateClass(), Equip::cGrenade::StaticCreateClass());
}

namespace unknown
{
    const char *cBoostPack::RetClassName() const
    {
        return "cBoostPack";
    }
}

#include "unknown/cBoostPack.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cBoostPack> cBoostPackScriptRegistrar(
        "cBoostPack", "cGrenade");
}
