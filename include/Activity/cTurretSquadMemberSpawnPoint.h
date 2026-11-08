// Activity::cTurretSquadMemberSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DF088, MakeNew 0x823DF128, from its registrars in CD2's
// initializer run); RuffKing names the class in cTurretSquadMemberSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H
#define ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cTurretSquadMemberSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTurretSquadMemberSpawnPointClass;
    };
}

#endif // ACTIVITY_CTURRETSQUADMEMBERSPAWNPOINT_H
