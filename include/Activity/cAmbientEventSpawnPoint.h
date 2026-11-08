// Activity::cAmbientEventSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DAB18, MakeNew 0x823DABB8, from its registrars in CD2's
// initializer run); RuffKing names the class in cAmbientEventSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CAMBIENTEVENTSPAWNPOINT_H
#define ACTIVITY_CAMBIENTEVENTSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cAmbientEventSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAmbientEventSpawnPointClass;
    };
}

#endif // ACTIVITY_CAMBIENTEVENTSPAWNPOINT_H
