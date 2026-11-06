// src/Vehicle/cTruck.cpp: Vehicle::cTruck (include/Vehicle/cTruck.h). Definitions follow CD2's order: the static
// registrars' initializers (0x82FE94E8..0x82FE95C8), then the functions from 0x826CB3D8.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Vehicle/cTruck.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cTruck::ms_pcTruckClass = &cTruck::StaticCreateClass();

    // CD2 0x82FE9510: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTruckcCarInheritRegistrar(
        cTruck::StaticCreateClass(), cCar::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTruckRegistrar(
        "cTruck", cTruck::MakeNew, 0x3290, false);

    // CD2 0x82FE95C8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTruckSpawningRegistrar(
        cTruck::StaticCreateClass(), cTruck::SpawnFromPrototype);

    bool cTruck::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTruckClass->IsA(c);
    }

    RWS::CAttributeHandler *cTruck::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTruckPrototype(packet);
    }

    const char *cTruck::RetClassName() const
    {
        return "cTruck";
    }

    RWS::CAttributeHandler *cTruck::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cTruck;
        return 0;
    }

    Fun_Runtime::cClass &cTruck::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTruckClass = new Fun_Runtime::cClass(0x11, "cTruck", 0x3290);
        return *cTruckClass;
    }

    Fun_Runtime::RetVal cTruck::cTruckPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
