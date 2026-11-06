// src/Vehicle/Agency/cAgencyCar.cpp: Vehicle::cAgencyCar (include/Vehicle/cAgencyCar.h). The address range and its
// evidence are in config/splits.txt; RuffKing's object for it is cAgencyCar.obj. Definitions follow CD2's order: the
// static registrars' initializers (0x82FEB468..0x82FEB548), then the functions from 0x826EC098.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Vehicle/cAgencyCar.h"
#include "Vehicle/cAgencyCarPrototype.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cAgencyCar::ms_pcAgencyCarClass = &cAgencyCar::StaticCreateClass();

    // CD2 0x82FEB490: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyCarcCarInheritRegistrar(
        cAgencyCar::StaticCreateClass(), cCar::StaticCreateClass());

    // CD2 0x82FEB4F8 (initializer) and 0x83040A50 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cAgencyCarRegistrar(
        "cAgencyCar", cAgencyCar::MakeNew, 0x30B0, false);

    // CD2 0x82FEB548: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyCarSpawningRegistrar(
        cAgencyCar::StaticCreateClass(), cAgencyCar::SpawnFromPrototype);

    const Fun_Runtime::cClass &cAgencyCar::RetClass() const
    {
        return *ms_pcAgencyCarClass;
    }

    bool cAgencyCar::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgencyCarClass->IsA(c);
    }

    RWS::CAttributeHandler *cAgencyCar::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyCarPrototype(packet);
    }

    const char *cAgencyCar::RetClassName() const
    {
        return "cAgencyCar";
    }

    RWS::CAttributeHandler *cAgencyCar::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAgencyCar;
        return 0;
    }

    Fun_Runtime::RetVal cAgencyCarPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    Fun_Runtime::cClass &cAgencyCar::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyCarClass = new Fun_Runtime::cClass(0x12062, "cAgencyCar", 0x30B0);
        return *cAgencyCarClass;
    }
}
