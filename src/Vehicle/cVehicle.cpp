// src/Vehicle/cVehicle.cpp: Vehicle::cVehicle (include/Vehicle/cVehicle.h). The address range and its evidence are in
// config/splits.txt; RuffKing's object for it is cVehicle.obj. Definitions follow CD2's order: the static registrars'
// initializers (0x82FE9948..0x82FE9A70), then the functions from 0x826CC708.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Vehicle/cVehicle.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cVehicle::ms_pcVehicleClass = &cVehicle::StaticCreateClass();

    // CD2 0x82FE9970: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVehiclecNetDynamicBodyInheritRegistrar(
        cVehicle::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());

    // CD2 0x82FE99D8: the class factory builds a cVehiclePrototype from a packet.
    static RWS::CClassFactory::CRegistrar cVehicleRegistrar(
        "cVehicle", cVehicle::MakeNew, 0x1740, false);

    // CD2 0x82FE9A28: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleSpawningRegistrar(
        cVehicle::StaticCreateClass(), cVehicle::SpawnFromPrototype);

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cVehicle> cVehicleScriptRegistrar(
        "cVehicle", "cDynamicBody");

    const Fun_Runtime::cClass &cVehicle::RetClass() const
    {
        return *ms_pcVehicleClass;
    }

    RWS::CAttributeHandler *cVehicle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehiclePrototype(packet);
    }

    const char *cVehicle::RetClassName() const
    {
        return "cVehicle";
    }

    RWS::CAttributeHandler *cVehicle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cVehicle;
        return 0;
    }

    float cVehicle::RetTheoreticalMaxMPH()
    {
        return Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
    }

    void cVehicle::SetIsBeingHiJackedByAI(bool bHiJacked)
    {
        m_bIsBeingHiJackedByAI = bHiJacked;
    }

    Fun_Runtime::cClass &cVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x1, "cVehicle", 0x1740);
        return *descriptor;
    }
    bool cVehicle::CreateParts(const char **names, unsigned short count)
    {
        return LocateParts(names, count);
    }

    int cVehicle::RetNumberOfSeats()
    {
        return m_VehicleSeats.size();
    }

    unsigned short cVehicle::RetCollisionSystemGroup()
    {
        return m_nSystemGroup;
    }

}
