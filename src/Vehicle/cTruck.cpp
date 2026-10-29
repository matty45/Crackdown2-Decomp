// src/Vehicle/cTruck.cpp
//
// Class: cTruck (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cTruck.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/cTruck.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/cTruck.cpp

#include "Vehicle/cTruck.h"

namespace Vehicle
{
    const Fun_Runtime::cClass *cTruck::ms_pcTruckClass = 0;

    bool cTruck::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTruckClass->IsA(c);
    }
}

