// AI::cTrainingDoorSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8247EA50, MakeNew 0x8247EC38, from its registrars in CD2's
// initializer run); RuffKing names the class in cTrainingDoorSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPoint from CD2's inheritance registrar.
#ifndef AI_CTRAININGDOORSPAWNPOINT_H
#define AI_CTRAININGDOORSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace AI
{
    class cTrainingDoorSpawnPoint : public Activity::cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingDoorSpawnPointClass;
    };
}

#endif // AI_CTRAININGDOORSPAWNPOINT_H
