// src/Vehicle/cLandVehicle.cpp: Vehicle::cLandVehicle (include/Vehicle/cLandVehicle.h). Definitions follow CD2's order:
// the static registrars' initializers (0x82FE8990..0x82FE8A70), then the functions from 0x826C0DB8.

#include "Vehicle/cLandVehicle.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cLandVehicle::ms_pcLandVehicleClass = &cLandVehicle::StaticCreateClass();

    // CD2 0x82FE89B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cLandVehiclecVehicleInheritRegistrar(
        cLandVehicle::StaticCreateClass(), cVehicle::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cLandVehicleRegistrar(
        "cLandVehicle", cLandVehicle::MakeNew, 0x28C0, false);

    // CD2 0x82FE8A70: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cLandVehicleSpawningRegistrar(
        cLandVehicle::StaticCreateClass(), cLandVehicle::SpawnFromPrototype);

    const Fun_Runtime::cClass &cLandVehicle::RetClass() const
    {
        return *ms_pcLandVehicleClass;
    }

    bool cLandVehicle::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcLandVehicleClass->IsA(c);
    }

    RWS::CAttributeHandler *cLandVehicle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cLandVehiclePrototype(packet);
    }

    const char *cLandVehicle::RetClassName() const
    {
        return "cLandVehicle";
    }

    RWS::CAttributeHandler *cLandVehicle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cLandVehicle;
        return 0;
    }

    Fun_Runtime::cClass &cLandVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLandVehicleClass = new Fun_Runtime::cClass(0x642, "cLandVehicle", 0x28C0);
        return *cLandVehicleClass;
    }

    void cLandVehicle::SetMustStop(bool mustStop)
    {
        m_bMustStop = mustStop;
    }

    Fun_Runtime::RetVal cLandVehicle::cLandVehiclePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
