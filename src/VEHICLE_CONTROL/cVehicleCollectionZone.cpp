// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "VEHICLE_CONTROL/cVehicleCollectionZone.h"
#include "rws/classfactory.h"

namespace VEHICLE_CONTROL
{
    const Fun_Runtime::cClass *cVehicleCollectionZone::ms_pcVehicleCollectionZoneClass = &cVehicleCollectionZone::StaticCreateClass();

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
    "cVehicleCollectionZone", VEHICLE_CONTROL::cVehicleCollectionZone::MakeNew, 0x210, false);   // CD2 0x83006B88
