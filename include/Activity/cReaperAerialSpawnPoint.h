// Activity::cReaperAerialSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D1888, MakeNew 0x823D1928, from its registrars in CD2's
// initializer run); RuffKing names the class in cReaperAerialSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CREAPERAERIALSPAWNPOINT_H
#define ACTIVITY_CREAPERAERIALSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cReaperAerialSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcReaperAerialSpawnPointClass;
    };
}

#endif // ACTIVITY_CREAPERAERIALSPAWNPOINT_H
