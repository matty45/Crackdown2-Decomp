// Activity::cTurretSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D4030, MakeNew 0x823D40D0, from its registrars in CD2's
// initializer run); RuffKing names the class in cTurretSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CTURRETSPAWNPOINT_H
#define ACTIVITY_CTURRETSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cTurretSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTurretSpawnPointClass;
    };
}

#endif // ACTIVITY_CTURRETSPAWNPOINT_H
