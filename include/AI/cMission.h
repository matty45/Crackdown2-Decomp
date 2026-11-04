// AI::cMission (Crackdown 2): STAND-IN with only its runtime class descriptor; its layout is not modelled yet.
// Its StaticCreateClass is CD2 0x82459250 (names the class "cMission"); derived classes register it as their parent. Name and namespace: RuffKing AI/Mission/cMission.h.
#ifndef AI_CMISSION_H
#define AI_CMISSION_H

#include "fun_runtime/class.h"

namespace AI
{
    class cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // AI_CMISSION_H
