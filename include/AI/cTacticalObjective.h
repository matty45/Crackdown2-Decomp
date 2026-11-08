// AI::cTacticalObjective (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824759A8, MakeNew 0x824757F8, from its registrars in CD2's
// initializer run); RuffKing names the class in cTacticalObjective.obj. No layout or virtuals are modelled yet;
// base AI::cMission from CD2's inheritance registrar.
#ifndef AI_CTACTICALOBJECTIVE_H
#define AI_CTACTICALOBJECTIVE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMission.h"

namespace AI
{
    class cTacticalObjective : public cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTacticalObjectiveClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CTACTICALOBJECTIVE_H
