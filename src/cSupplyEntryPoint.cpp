#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
// src/cSupplyEntryPoint.cpp
//
// Class: cSupplyEntryPoint (namespace: unknown). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSupplyEntryPoint.cpp

#include "unknown/cSupplyEntryPoint.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSupplyEntryPoint::ms_pcSupplyEntryPointClass = &cSupplyEntryPoint::StaticCreateClass();

    Fun_Runtime::cClass &cSupplyEntryPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSupplyEntryPointClass = new Fun_Runtime::cClass(0x101F, "cSupplyEntryPoint", 0x140);
        return *cSupplyEntryPointClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cSupplyEntryPointRegistrar(
        "cSupplyEntryPoint", cSupplyEntryPoint::MakeNew, 0x140, false);
}

// CD2 0x82FF94E0: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cSupplyEntryPointcGameBaseInheritRegistrar(
        unknown::cSupplyEntryPoint::StaticCreateClass(), cGameBase::StaticCreateClass());
}
