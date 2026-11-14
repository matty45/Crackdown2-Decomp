// Kaim::CEntity (Crackdown 2): STAND-IN for the name only. RenderWare AI's (Kynapse) entity base; RuffKing's
// AI::cDynamicObstacle derives from it, and CD2's IsAIEntityOwner overrides (cProp's 0x8272C3E8) compare an entity
// pointer with the owner's dynamic obstacle, as RuffKing's do. Layout and virtuals are not modelled.
#ifndef KAIM_CENTITY_H
#define KAIM_CENTITY_H

namespace Kaim
{
    class CEntity
    {
    };
}

#endif // KAIM_CENTITY_H
