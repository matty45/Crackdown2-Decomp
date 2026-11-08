// Activity::cSquadMemberSpawnPointBase (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DD270, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadMemberSpawnPointBase.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H
#define ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace Activity
{
    class cSquadMemberSpawnPointBase : public cSpawnPointBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadMemberSpawnPointBaseClass;
    };
}

#endif // ACTIVITY_CSQUADMEMBERSPAWNPOINTBASE_H
