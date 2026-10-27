#ifndef VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H
#define VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace VEHICLE_CONTROL
{
    class cVehicleCollectionZone : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcVehicleCollectionZoneClass;

        cVehicleCollectionZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

