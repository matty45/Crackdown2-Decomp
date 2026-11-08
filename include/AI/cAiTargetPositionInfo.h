// AI::cAiTargetPositionInfo (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82451708, from its registrars in CD2's
// initializer run); RuffKing names the class in cAiTargetPositionInfo.obj. No layout or virtuals are modelled yet;
// base AI::cAiTargetInfo from CD2's inheritance registrar.
#ifndef AI_CAITARGETPOSITIONINFO_H
#define AI_CAITARGETPOSITIONINFO_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cAiTargetInfo.h"

namespace AI
{
    class cAiTargetPositionInfo : public cAiTargetInfo
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAiTargetPositionInfoClass;
    };
}

#endif // AI_CAITARGETPOSITIONINFO_H
