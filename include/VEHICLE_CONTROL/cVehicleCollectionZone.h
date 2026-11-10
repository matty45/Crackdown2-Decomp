#ifndef VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H
#define VEHICLE_CONTROL_CVEHICLECOLLECTIONZONE_H

#include "AI/cHeliCallZone.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace VEHICLE_CONTROL
{
    // RuffKing's base. CD2's table (0x820083B8) holds this class's RetClass, IsA and RetClassName in slots 18 to 20,
    // where cHeliCallZone declares them.
    class cVehicleCollectionZone : public AI::cHeliCallZone
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
        // CD2: cVehicleCollectionZone's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82786948
        virtual void OnPlayerEnter(CHARACTER::cCharacter *); // 16: 0x82786A18
        virtual void OnPlayerLeave(CHARACTER::cCharacter *); // 17: 0x82786FF8
    };
}

#endif

