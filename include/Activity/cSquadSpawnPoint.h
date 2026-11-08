// Activity::cSquadSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DD810, MakeNew 0x823DD8B0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSQUADSPAWNPOINT_H
#define ACTIVITY_CSQUADSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace Activity
{
    class cSquadSpawnPoint : public cSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadSpawnPointClass;
    };
}

#endif // ACTIVITY_CSQUADSPAWNPOINT_H
