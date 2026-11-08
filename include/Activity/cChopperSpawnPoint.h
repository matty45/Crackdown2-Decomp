// Activity::cChopperSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DB8A8, MakeNew 0x823DB948, from its registrars in CD2's
// initializer run); RuffKing names the class in cChopperSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSquadMemberSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CCHOPPERSPAWNPOINT_H
#define ACTIVITY_CCHOPPERSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSquadMemberSpawnPoint.h"

namespace Activity
{
    class cChopperSpawnPoint : public cSquadMemberSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcChopperSpawnPointClass;
    };
}

#endif // ACTIVITY_CCHOPPERSPAWNPOINT_H
