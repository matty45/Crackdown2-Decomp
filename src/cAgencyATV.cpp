#include "rws/classfactory.h"
// src/cAgencyATV.cpp
//
// Class: cAgencyATV (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAgencyATV.cpp

#include "unknown/cAgencyATV.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAgencyATV::ms_pcAgencyATVClass = &cAgencyATV::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyATV::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyATVClass = new Fun_Runtime::cClass(0x12065, "cAgencyATV", 0x31F0);
        return *cAgencyATVClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cAgencyATVRegistrar(
        "cAgencyATV", cAgencyATV::MakeNew, 0x31F0, false);
}
