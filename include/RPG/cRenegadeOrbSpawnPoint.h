// RPG::cRenegadeOrbSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x827588A8, MakeNew 0x82758940, from its registrars in CD2's
// initializer run); RuffKing names the class in cRenegadeOrbSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef RPG_CRENEGADEORBSPAWNPOINT_H
#define RPG_CRENEGADEORBSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace RPG
{
    class cRenegadeOrbSpawnPoint : public Activity::cSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbSpawnPointClass;
    };
}

#endif // RPG_CRENEGADEORBSPAWNPOINT_H
