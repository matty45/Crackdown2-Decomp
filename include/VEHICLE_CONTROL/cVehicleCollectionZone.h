#ifndef VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H
#define VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace VEHICLE_CONTROL
{
    class cVehicleCollectionZone : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83006AD0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cVehicleCollectionZoneClass = new Fun_Runtime::cClass(0x1B3BC, "cVehicleCollectionZone", 0x210);
            return *cVehicleCollectionZoneClass;
        }
        static const Fun_Runtime::cClass *ms_pcVehicleCollectionZoneClass;

        cVehicleCollectionZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

