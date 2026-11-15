// Activity::cTurretVehicleSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D4A88, MakeNew 0x823D4B28, from its registrars in CD2's
// initializer run); RuffKing names the class in cTurretVehicleSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CTURRETVEHICLESPAWNPOINT_H
#define ACTIVITY_CTURRETVEHICLESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cTurretVehicleSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        // CD2 0x823D4A18 / 0x823D4A28: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTurretVehicleSpawnPointClass;
    };
}

#endif // ACTIVITY_CTURRETVEHICLESPAWNPOINT_H
