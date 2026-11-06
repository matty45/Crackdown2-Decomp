// src/cTransformingCar.cpp
//
// Class: cTransformingCar (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cTransformingCar.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "unknown/cTransformingCar.h"
#include "cd2/memory.h"
#include "unknown/cTransformingCarPrototype.h"
#include "unknown/cTransforming.h"
#include "Vehicle/cCar.h"
#include "fun_runtime/inheritance_registrar.h"

namespace unknown
{
    const Fun_Runtime::cClass *cTransformingCar::ms_pcTransformingCarClass = &cTransformingCar::StaticCreateClass();

    Fun_Runtime::cClass &cTransformingCar::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTransformingCarClass = new Fun_Runtime::cClass(0x14, "cTransformingCar", 0x67D0);
        return *cTransformingCarClass;
    }

    // CD2 0x82FE7100 and 0x82FE7168: runtime class inheritance registration under both parents.
    static Fun_Runtime::cInheritanceRegistrar cTransformingCarcCarInheritRegistrar(
        unknown::cTransformingCar::StaticCreateClass(), Vehicle::cCar::StaticCreateClass());

    static Fun_Runtime::cInheritanceRegistrar cTransformingCarcTransformingInheritRegistrar(
        unknown::cTransformingCar::StaticCreateClass(), unknown::cTransforming::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTransformingCarRegistrar(
        "cTransformingCar", cTransformingCar::MakeNew, 0x67D0, false);

    // CD2 0x82FE7220: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTransformingCarSpawningRegistrar(
        cTransformingCar::StaticCreateClass(), cTransformingCar::SpawnFromPrototype);

    RWS::CAttributeHandler *cTransformingCar::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTransformingCarPrototype(packet);
    }

    const char *cTransformingCar::RetClassName() const
    {
        return "cTransformingCar";
    }

    Fun_Runtime::RetVal cTransformingCarPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
