// src/cZoneManager.cpp
//
// Class: cZoneManager (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cZoneManager.cpp

#include "unknown/cZoneManager.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cZoneManager::ms_pcZoneManagerClass = &cZoneManager::StaticCreateClass();

    Fun_Runtime::cClass &cZoneManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cZoneManagerClass = new Fun_Runtime::cClass(0x60E, "cZoneManager", 0x84);
        return *cZoneManagerClass;
    }
}
