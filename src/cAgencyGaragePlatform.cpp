#include "rws/classfactory.h"
// src/cAgencyGaragePlatform.cpp
//
// Class: cAgencyGaragePlatform (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAgencyGaragePlatform.cpp

#include "unknown/cAgencyGaragePlatform.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAgencyGaragePlatform::ms_pcAgencyGaragePlatformClass = &cAgencyGaragePlatform::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyGaragePlatform::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyGaragePlatformClass = new Fun_Runtime::cClass(0x1024, "cAgencyGaragePlatform", 0xEE0);
        return *cAgencyGaragePlatformClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cAgencyGaragePlatformRegistrar(
        "cAgencyGaragePlatform", cAgencyGaragePlatform::MakeNew, 0xEE0, false);
}
