// Activity::cSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D1D00, MakeNew 0x823D1DA0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSPAWNPOINT_H
#define ACTIVITY_CSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace Activity
{
    class cSpawnPoint : public cSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSpawnPointClass;
    };
}

#endif // ACTIVITY_CSPAWNPOINT_H
