// src/cTeleporterDoor.cpp
//
// Class: cTeleporterDoor (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cTeleporterDoor.cpp

#include "unknown/cTeleporterDoor.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cTeleporterDoor::ms_pcTeleporterDoorClass = &cTeleporterDoor::StaticCreateClass();

    Fun_Runtime::cClass &cTeleporterDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTeleporterDoorClass = new Fun_Runtime::cClass(0x1022, "cTeleporterDoor", 0xEF0);
        return *cTeleporterDoorClass;
    }
}
