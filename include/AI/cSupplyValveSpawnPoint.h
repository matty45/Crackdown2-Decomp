// AI::cSupplyValveSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82200B80, MakeNew 0x82458AF8, from its registrars in CD2's
// initializer run); RuffKing names the class in cSupplyValveSpawnPoint.obj. No layout or virtuals are modelled yet;
// base AI::cRefineryPropSpawnPoint from CD2's inheritance registrar.
#ifndef AI_CSUPPLYVALVESPAWNPOINT_H
#define AI_CSUPPLYVALVESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cRefineryPropSpawnPoint.h"

namespace AI
{
    class cSupplyValveSpawnPoint : public cRefineryPropSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSupplyValveSpawnPointClass;
    };
}

#endif // AI_CSUPPLYVALVESPAWNPOINT_H
