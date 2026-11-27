// CHARACTER controller-event enums (Crackdown 2): RuffKing's eControllerEventType, eControllerEventSubType and
// eControllerEvents, the arguments of cAgent::EventTrigger, and etActionTypesEnum, the first argument of
// cAgent::EventAnimation. The values are RuffKing's and agree with CD2's agents: cDropAgent's EventTrigger (0x8240BDF0)
// acts on (3, 5, 3) = eCET_Props, eCEST_Drop, eCE_Finished; cSecondaryFireAgent's (0x8241D440) on (2, 13, 1) =
// eCET_Equipment, eCEST_Thrown, eCE_Started; cPrimaryFireAgent's EventAnimation (0x8241A7D8) on ACTION_ARM (2). The
// header name is ours.
#ifndef CHARACTER_CONTROLLEREVENTS_H
#define CHARACTER_CONTROLLEREVENTS_H

namespace CHARACTER
{
    enum eControllerEventType
    {
        eCET_None = 0,
        eCET_Generic,
        eCET_Equipment,
        eCET_Props,
        eCET_Vehicle,
        eCET_Movement,
        eCET_Hand2Hand,
        eCET_Stand,
    };

    enum eControllerEventSubType
    {
        eCEST_None = 0,
        eCEST_Jump,
        eCEST_FullBodyPlayback,
        eCEST_UpperBodyPlayback,
        eCEST_PickUp,
        eCEST_Drop,
        eCEST_Lost,
        eCEST_Store,
        eCEST_Equip,
        eCEST_AutoEquip,
        eCEST_Swaped,
        eCEST_Fire,
        eCEST_Reload,
        eCEST_Thrown,
        eCEST_Detonate,
        eCEST_Barge,
        eCEST_GetIn,
        eCEST_GetOut,
        eCEST_Interaction,
        eCEST_Punch,
        eCEST_StunnedRecover,
        eCEST_180,
    };

    enum eControllerEvents
    {
        eCE_None = 0,
        eCE_Started,
        eCE_Failed,
        eCE_Finished,
        eCE_Interupted,
        eCE_Looped,
    };

    enum etActionTypesEnum
    {
        ACTION_HANDLED = 0,
        ACTION_BASE,
        ACTION_ARM,
    };
}

#endif // CHARACTER_CONTROLLEREVENTS_H
