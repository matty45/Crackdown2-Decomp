#include "rws/classfactory.h"
// src/cSticklerGrenade.cpp
//
// Class: cSticklerGrenade (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSticklerGrenade.cpp

#include "unknown/cSticklerGrenade.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSticklerGrenade::ms_pcSticklerGrenadeClass = &cSticklerGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cSticklerGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSticklerGrenadeClass = new Fun_Runtime::cClass(0x10144, "cSticklerGrenade", 0x9E0);
        return *cSticklerGrenadeClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cSticklerGrenadeRegistrar(
        "cSticklerGrenade", cSticklerGrenade::MakeNew, 0x9E0, false);
}

// CD2 0x82623240.
namespace unknown
{
    const char *cSticklerGrenade::RetClassName() const
    {
        return "cSticklerGrenade";
    }
}
