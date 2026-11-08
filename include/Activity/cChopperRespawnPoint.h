// Activity::cChopperRespawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DB588, MakeNew 0x823DB628, from its registrars in CD2's
// initializer run); RuffKing names the class in cChopperRespawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberRespawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CCHOPPERRESPAWNPOINT_H
#define ACTIVITY_CCHOPPERRESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberRespawnPoint.h"

namespace Activity
{
    class cChopperRespawnPoint : public cSquadMemberRespawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcChopperRespawnPointClass;
    };
}

#endif // ACTIVITY_CCHOPPERRESPAWNPOINT_H
