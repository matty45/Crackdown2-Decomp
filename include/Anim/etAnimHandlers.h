// Handler names/order from RuffKing; CD2 allocates fifty profile slots (0x824DFFE0).
#ifndef ANIM_ETANIMHANDLERS_H
#define ANIM_ETANIMHANDLERS_H
namespace Anim
{
    enum etAnimHandlers
    {
        eHandlerNone = -1,
        eHandlerBasePose = 0, eHandlerStand, eHandlerStandTurn, eHandlerCrouch,
        eHandlerRunWalk, eHandlerSprint, eHandlerBarge, eHandlerGoliath,
        eHandlerReaction, eHandlerRappel, eHandlerJumpLaunch, eHandlerJump,
        eHandlerJumpLand, eHandlerJumpLandFast, eHandlerWingSuit, eHandlerSwim,
        eHandlerSwimLaunch, eHandlerLedge, eHandlerLedgeLaunch, eHandlerLandVehicle,
        eHandlerDamage, eHandlerDeath, eHandlerStunned, eHandlerGenericFull,
        eHandlerPropPickUpFull, eHandlerH2HFull, eHandlerTransformation,
        eHandlerPropPickUp, eHandlerPropCarry, eHandlerPropCarry_NPC,
        eHandlerPropDrop, eHandlerPropThrow, eHandlerPropThrow_NPC,
        eHandlerEquipmentPickUp, eHandlerEquipmentCarry, eHandlerEquipmentSwap,
        eHandlerEquipmentAimAndFire, eHandlerEquipmentReload, eHandlerEquipmentThrow,
        eHandlerEquipmentDetonator, eHandlerEquipmentThrowFull_NPC, eHandlerH2HUpper,
        eHandlerGenericUpper, eHandlerCrowd, eHandlerCover, eHandlerPropInteraction,
        eHandlerJump_NPC, eHandlerTurrets, eHandlerBeaconPulseHover,
        eHandlerReaperPropAttack, eNumHandlers
    };
}
#endif
