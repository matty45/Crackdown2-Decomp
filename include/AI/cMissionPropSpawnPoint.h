// AI::cMissionPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8245BF28, MakeNew 0x8245BFC8, from its registrars in CD2's
// initializer run); RuffKing names the class in cMissionPropSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPoint from CD2's inheritance registrar.
#ifndef AI_CMISSIONPROPSPAWNPOINT_H
#define AI_CMISSIONPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace AI
{
    class cMissionPropSpawnPoint : public Activity::cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcMissionPropSpawnPointClass;
    };
}

#endif // AI_CMISSIONPROPSPAWNPOINT_H
