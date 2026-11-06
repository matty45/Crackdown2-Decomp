// src/cTransformingTruck.cpp
//
// Class: cTransformingTruck (namespace: unknown). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cTransformingTruck.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Vehicle/cTruck.h"
#include "rws/classfactory.h"
#include "unknown/cTransformingTruck.h"
#include "cd2/memory.h"
#include "unknown/cTransformingTruckPrototype.h"
#include "unknown/cTransforming.h"

namespace unknown
{
    const Fun_Runtime::cClass *cTransformingTruck::ms_pcTransformingTruckClass = &cTransformingTruck::StaticCreateClass();

    Fun_Runtime::cClass &cTransformingTruck::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTransformingTruckClass = new Fun_Runtime::cClass(0x15, "cTransformingTruck", 0x69E0);
        return *cTransformingTruckClass;
    }

    static RWS::CClassFactory::CRegistrar cTransformingTruckRegistrar(
        "cTransformingTruck", cTransformingTruck::MakeNew, 0x69E0, false);

    // CD2 0x82FE75D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTransformingTruckcTruckInheritRegistrar(
        unknown::cTransformingTruck::StaticCreateClass(), Vehicle::cTruck::StaticCreateClass());

    // CD2 0x82FE7640: runtime class inheritance registration under its second parent.
    static Fun_Runtime::cInheritanceRegistrar cTransformingTruckcTransformingInheritRegistrar(
        unknown::cTransformingTruck::StaticCreateClass(), unknown::cTransforming::StaticCreateClass());

    // CD2 0x82FE76F8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTransformingTruckSpawningRegistrar(
        cTransformingTruck::StaticCreateClass(), cTransformingTruck::SpawnFromPrototype);

    const char *cTransformingTruck::RetClassName() const
    {
        return "cTransformingTruck";
    }

    Fun_Runtime::RetVal cTransformingTruckPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
