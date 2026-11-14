// AI::cMissionCriticalPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8245B740, MakeNew 0x8245B7D8, from its registrars in CD2's
// initializer run); RuffKing names the class in cMissionCriticalPropSpawnPoint.obj.
// Base Activity::cSpawnPoint comes from CD2's inheritance registrar; the additional
// replication bases and instance fields remain unrecovered here.
#ifndef AI_CMISSIONCRITICALPROPSPAWNPOINT_H
#define AI_CMISSIONCRITICALPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace AI
{
    class cMissionCriticalPropSpawnPoint : public Activity::cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropSpawnPointClass;
        // cSpawnPointBase supplies primary slots 0..10. CD2's Docks mission
        // calls these two new slots through its collection-object pointer
        // (0x824746F0 / 0x82474740); names/signatures agree with RuffKing.
        virtual void InitReplication(); // primary slot 11
        virtual void TermReplication(); // primary slot 12
    };
}

#endif // AI_CMISSIONCRITICALPROPSPAWNPOINT_H
