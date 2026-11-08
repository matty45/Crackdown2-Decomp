// Activity::cSquadMemberRespawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x821D1BB8, MakeNew 0x823DBE90, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadMemberRespawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSQUADMEMBERRESPAWNPOINT_H
#define ACTIVITY_CSQUADMEMBERRESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPointBase.h"

namespace Activity
{
    class cSquadMemberRespawnPoint : public cSquadMemberSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadMemberRespawnPointClass;
    };
}

#endif // ACTIVITY_CSQUADMEMBERRESPAWNPOINT_H
