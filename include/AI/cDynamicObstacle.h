// AI::cDynamicObstacle (Crackdown 2): STAND-IN for the name, base and two members only. Names, base and signatures from
// RuffKing (Ai/Entity/cDynamicObstacle.h). CD2's cVehicle::GetDynamicObstacleInput (0x826CE590) tail-calls GetInput with the
// owning object, and cVehicle::CreateDynamicObstacle (0x826CE520) calls SetDimensions with it, as RuffKing's do. Layout
// and virtuals are not modelled.
#ifndef AI_CDYNAMICOBSTACLE_H
#define AI_CDYNAMICOBSTACLE_H

#include "Kaim/CEntity.h"

class cGameBase;

namespace AI
{
    class cDynamicObstacle : public Kaim::CEntity
    {
    public:
        unsigned char GetInput(cGameBase *pGB);     // CD2 0x822D1080
        void SetDimensions(cGameBase *pGB);         // CD2 0x82279D00
    };
}

#endif // AI_CDYNAMICOBSTACLE_H
