// AI::cMissionBase (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x8245A6A8 (names the class "cMissionBase"); derived classes register it as their parent. Name and namespace: RuffKing AI/Mission/cMissionBase.h.
#ifndef AI_CMISSIONBASE_H
#define AI_CMISSIONBASE_H

#include "fun_runtime/class.h"

namespace AI
{
    class cMissionBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // AI_CMISSIONBASE_H
