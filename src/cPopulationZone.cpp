#include "rws/classfactory.h"
// src/cPopulationZone.cpp
//
// Class: cPopulationZone (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cPopulationZone.cpp

#include "unknown/cPopulationZone.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cPopulationZone::ms_pcPopulationZoneClass = &cPopulationZone::StaticCreateClass();

    Fun_Runtime::cClass &cPopulationZone::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPopulationZoneClass = new Fun_Runtime::cClass(0x416, "cPopulationZone", 0x150);
        return *cPopulationZoneClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cPopulationZoneRegistrar(
        "cPopulationZone", cPopulationZone::MakeNew, 0x150, false);
}
