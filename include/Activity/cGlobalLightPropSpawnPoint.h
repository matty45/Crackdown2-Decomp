// Activity::cGlobalLightPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D0FC8, MakeNew 0x823D1068, from its registrars in CD2's
// initializer run); RuffKing names the class in cGlobalLightPropSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPoint from CD2's inheritance registrar.
#ifndef ACTIVITY_CGLOBALLIGHTPROPSPAWNPOINT_H
#define ACTIVITY_CGLOBALLIGHTPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace Activity
{
    class cGlobalLightPropSpawnPoint : public cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGlobalLightPropSpawnPointClass;
    };
}

#endif // ACTIVITY_CGLOBALLIGHTPROPSPAWNPOINT_H
