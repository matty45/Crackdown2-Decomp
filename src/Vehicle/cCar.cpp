// src/Vehicle/cCar.cpp: Vehicle::cCar (include/Vehicle/cCar.h). The address range and its evidence are in
// config/splits.txt; RuffKing's object for it is cCar.obj. Definitions follow CD2's order: the static registrars'
// initializers (0x82FE7A50..0x82FE7B30), then the functions from 0x826B5CA8.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Vehicle/cCar.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cCar::ms_pcCarClass = &cCar::StaticCreateClass();

    // CD2 0x82FE7A78: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCarcWheelGroupInheritRegistrar(
        cCar::StaticCreateClass(), cWheelGroup::StaticCreateClass());

    // CD2 0x82FE7AE0 (initializer) and 0x830407B0 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cCarRegistrar(
        "cCar", cCar::MakeNew, 0x3070, false);

    // CD2 0x82FE7B30: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCarSpawningRegistrar(
        cCar::StaticCreateClass(), cCar::SpawnFromPrototype);

    const Fun_Runtime::cClass &cCar::RetClass() const
    {
        return *ms_pcCarClass;
    }

    bool cCar::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCarClass->IsA(c);
    }

    RWS::CAttributeHandler *cCar::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCarPrototype(packet);
    }

    const char *cCar::RetClassName() const
    {
        return "cCar";
    }

    RWS::CAttributeHandler *cCar::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCar;
        return 0;
    }

    Fun_Runtime::cClass &cCar::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCarClass = new Fun_Runtime::cClass(0x10, "cCar", 0x3070);
        return *cCarClass;
    }

    Fun_Runtime::RetVal cCar::cCarPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
