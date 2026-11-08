// Activity::cWeaponVehicleRespawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DF670, MakeNew 0x823DF710, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeaponVehicleRespawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberRespawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CWEAPONVEHICLERESPAWNPOINT_H
#define ACTIVITY_CWEAPONVEHICLERESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberRespawnPoint.h"

namespace Activity
{
    class cWeaponVehicleRespawnPoint : public cSquadMemberRespawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcWeaponVehicleRespawnPointClass;
    };
}

#endif // ACTIVITY_CWEAPONVEHICLERESPAWNPOINT_H
