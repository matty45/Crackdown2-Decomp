// src/CCarController.cpp
//
// Class: CCarController (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is CarController.obj.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CCarController.cpp

#include "unknown/CCarController.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *CCarController::ms_pCCarControllerClass = &CCarController::StaticCreateClass();

    Fun_Runtime::cClass &CCarController::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CCarControllerClass = new Fun_Runtime::cClass(0x929, "CCarController", 0xA30);
        return *CCarControllerClass;
    }
}
