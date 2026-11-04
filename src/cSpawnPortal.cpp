#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include "rws/classfactory.h"
// src/cSpawnPortal.cpp
//
// Class: cSpawnPortal (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSpawnPortal.cpp

#include "unknown/cSpawnPortal.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSpawnPortal::ms_pcSpawnPortalClass = &cSpawnPortal::StaticCreateClass();

    Fun_Runtime::cClass &cSpawnPortal::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpawnPortalClass = new Fun_Runtime::cClass(0x1025, "cSpawnPortal", 0xEC0);
        return *cSpawnPortalClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cSpawnPortalRegistrar(
        "cSpawnPortal", cSpawnPortal::MakeNew, 0xEC0, false);
}

// CD2 0x82FF8C10: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cSpawnPortalcHingedPropInheritRegistrar(
        unknown::cSpawnPortal::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());
}

// CD2 0x8273DF78.
namespace unknown
{
    const Fun_Runtime::cClass &cSpawnPortal::RetClass() const
    {
        return *ms_pcSpawnPortalClass;
    }
}

// CD2 0x8273E058.
namespace unknown
{
    const char *cSpawnPortal::RetClassName() const
    {
        return "cSpawnPortal";
    }
}
