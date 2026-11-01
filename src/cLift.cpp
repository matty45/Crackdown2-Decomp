#include "rws/classfactory.h"
// src/cLift.cpp
//
// Class: cLift (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cLift.cpp

#include "unknown/cLift.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cLift::ms_pcLiftClass = &cLift::StaticCreateClass();

    Fun_Runtime::cClass &cLift::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLiftClass = new Fun_Runtime::cClass(0x102B, "cLift", 0xF30);
        return *cLiftClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cLiftRegistrar(
        "cLift", cLift::MakeNew, 0xF30, false);
}
