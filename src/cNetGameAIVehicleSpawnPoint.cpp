// src/cNetGameAIVehicleSpawnPoint.cpp
//
// Class: cNetGameAIVehicleSpawnPoint (namespace: unknown). Set up automatically: no function is matched yet. The
// address range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cNetGameAIVehicleSpawnPoint.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "unknown/cNetGameAISpawnPoint.h"
#include "rws/classfactory.h"
#include "unknown/cNetGameAIVehicleSpawnPoint.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass &cNetGameAIVehicleSpawnPoint::RetClass() const
    {
        return *ms_pcNetGameAIVehicleSpawnPointClass;
    }

    bool cNetGameAIVehicleSpawnPoint::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcNetGameAIVehicleSpawnPointClass->IsA(testClass);
    }

    RWS::CAttributeHandler *cNetGameAIVehicleSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGameAIVehicleSpawnPoint;
    }

    const Fun_Runtime::cClass *cNetGameAIVehicleSpawnPoint::ms_pcNetGameAIVehicleSpawnPointClass = &cNetGameAIVehicleSpawnPoint::StaticCreateClass();

    Fun_Runtime::cClass &cNetGameAIVehicleSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cNetGameAIVehicleSpawnPointClass = new Fun_Runtime::cClass(0x489D, "cNetGameAIVehicleSpawnPoint", 0xB0);
        return *cNetGameAIVehicleSpawnPointClass;
    }

    static RWS::CClassFactory::CRegistrar cNetGameAIVehicleSpawnPointRegistrar(
        "cNetGameAIVehicleSpawnPoint", cNetGameAIVehicleSpawnPoint::MakeNew, 0xB0, false);

    // CD2 0x83016D08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cNetGameAIVehicleSpawnPointcNetGameAISpawnPointInheritRegistrar(
        unknown::cNetGameAIVehicleSpawnPoint::StaticCreateClass(), unknown::cNetGameAISpawnPoint::StaticCreateClass());

    const char *cNetGameAIVehicleSpawnPoint::RetClassName() const
    {
        return "cNetGameAIVehicleSpawnPoint";
    }
}
