#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "rws/classfactory.h"
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

namespace unknown
{
    static RWS::CClassFactory::CRegistrar CCarControllerRegistrar(
        "CCarController", CCarController::MakeNew, 0xA30, false);
}

// CD2 0x83004B28: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar CCarControllercVehicleControllerInheritRegistrar(
        unknown::CCarController::StaticCreateClass(), VEHICLE_CONTROL::cVehicleController::StaticCreateClass());
}

// CD2 0x83004BE0: register the class descriptor and placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar CCarControllerSpawningRegistrar(
        CCarController::StaticCreateClass(), CCarController::SpawnFromPrototype);
}

namespace unknown
{
    const char *CCarController::RetClassName() const
    {
        return "CCarController";
    }
}

namespace unknown
{
    const Fun_Runtime::cClass &CCarController::RetClass() const
    {
        return *ms_pCCarControllerClass;
    }
}

namespace unknown
{
    RWS::CAttributeHandler *CCarController::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CCarController;
        return 0;
    }
}
