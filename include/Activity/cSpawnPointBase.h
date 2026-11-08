// Activity::cSpawnPointBase (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D2A98, from its registrars in CD2's
// initializer run); RuffKing names the class in cSpawnPointBase.obj. No layout or virtuals are modelled yet.
#ifndef ACTIVITY_CSPAWNPOINTBASE_H
#define ACTIVITY_CSPAWNPOINTBASE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Activity
{
    class cSpawnPointBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSpawnPointBaseClass;
    };
}

#endif // ACTIVITY_CSPAWNPOINTBASE_H
