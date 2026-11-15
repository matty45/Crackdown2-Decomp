// AI::cRefineryPropSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824586F8, MakeNew 0x82458790, from its registrars in CD2's
// initializer run); RuffKing names the class in cRefineryPropSpawnPoint.obj. No layout or virtuals are modelled yet;
// base AI::cMissionCriticalPropSpawnPoint from CD2's inheritance registrar.
#ifndef AI_CREFINERYPROPSPAWNPOINT_H
#define AI_CREFINERYPROPSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMissionCriticalPropSpawnPoint.h"

namespace AI
{
    class cRefineryPropSpawnPoint : public cMissionCriticalPropSpawnPoint
    {
    public:
        // CD2 0x82458688 / 0x82458698: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcRefineryPropSpawnPointClass;
    };
}

#endif // AI_CREFINERYPROPSPAWNPOINT_H
