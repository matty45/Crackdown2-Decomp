#include "VEHICLE_CONTROL/cVehicleCollectionZone.h"
#include "rws/classfactory.h"

namespace VEHICLE_CONTROL
{
    const Fun_Runtime::cClass *cVehicleCollectionZone::ms_pcVehicleCollectionZoneClass = 0;

    cVehicleCollectionZone::cVehicleCollectionZone() {}

    const Fun_Runtime::cClass &cVehicleCollectionZone::RetClass() const
    {
        return *ms_pcVehicleCollectionZoneClass;
    }

    const char *cVehicleCollectionZone::RetClassName() const
    {
        return "cVehicleCollectionZone";
    }

    bool cVehicleCollectionZone::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVehicleCollectionZoneClass->IsA(c);
    }

    RWS::CAttributeHandler *cVehicleCollectionZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleCollectionZone();
    }
}

static RWS::CClassFactory::CRegistrar cVehicleCollectionZoneRegistrar(
    "cVehicleCollectionZone", VEHICLE_CONTROL::cVehicleCollectionZone::MakeNew, 0x7C, false);
