// PHYSICS::cDynamicBodyInteractionData (Crackdown 2): STAND-IN. Name, size (0x30) and the first members from RuffKing's
// PDB (also Burn's Physics/cdynamicbodyinteractiondata.h). CD2's cHelicopter::HandleTryToEnterInteractPermissionQuery
// (0x826BDDA0) reads m_nSubItem at +8, as RuffKing's does. The rest is not modelled.
#ifndef PHYSICS_CDYNAMICBODYINTERACTIONDATA_H
#define PHYSICS_CDYNAMICBODYINTERACTIONDATA_H

#include "cd2/layout.h"

namespace PHYSICS
{
    // RuffKing's interaction states (its PDB values); CD2's vehicle permission queries store 0x17..0x20 as these.
    enum eInteractionType
    {
        eDBIT_NONE = 0,
        eDBIT_INTERACT,
        eDBIT_INTERACT_FINISHED,
        eDBIT_TRY_TO_EJECT_CHARCTER,
        eDBIT_EJECT_CHARACTER,
        eDBIT_EJECT_CHARACTER_FAIL,
        eDBIT_EJECT_CHARACTER_RETRY,
        eDBIT_EJECT_CHARACTER_FINISHED,
        eDBIT_TRY_TO_ENTER,
        eDBIT_ENTER,
        eDBIT_ENTER_FAIL,
        eDBIT_ENTER_RETRY,
        eDBIT_ENTER_FINISED,
        eDBIT_OPEN_DOOR,
        eDBIT_OPEN_DOOR_FAIL,
        eDBIT_PULL_OUT,
        eDBIT_TRY_TO_EXIT,
        eDBIT_EXIT,
        eDBIT_EXIT_RETRY,
        eDBIT_EXIT_BAIL,
        eDBIT_EXIT_ADVANCED_WINDOW,
        eDBIT_EXIT_ADVANCED_CRAWL,
        eDBIT_EXIT_WARP,
        eDBIT_EXIT_FAIL,
        eDBIT_FORCED_EXIT_WARP,
        eDBIT_FORCED_EXIT_BAIL,
        eDBIT_FORCED_EXIT,
        eDBIT_EXIT_FINISED,
        eDBIT_TRY_TO_CLOSE_DOOR,
        eDBIT_TRY_TO_CLOSE_ALTERNATIVE_DOOR,
        eDBIT_CLOSE_DOOR,
        eDBIT_CLOSE_ALTERNATIVE_DOOR,
        eDBIT_CLOSE_DOOR_FAIL,
        eDBIT_CLOSE_DOOR_FINISH,
        eDBIT_TRY_TO_SWAP_SEATS,
        eDBIT_SWAP_SEATS,
        eDBIT_SWAP_SEATS_FAIL,
        eDBIT_SWAP_SEATS_FINISHED,
        eDBIT_INSIDE_EJECTION_FAIL_FINISH,
        eDBIT_OPEN_DOOR_FINISH,
        eDBIT_TRY_TO_EJECT_CHARACTERS,
        eDBIT_EJECTION_FAIL,
        eDBIT_EJECTION_SUCCESS,
        eDBIT_VEHICLE_INTERACTION_FINISHED,
        eDBIT_MAX,
    };

    class cDynamicBodyInteractionData
    {
    public:
        unsigned int m_nFromID;                         // 0x0
        eInteractionType m_eInteraction;                // 0x4
        unsigned int m_nSubItem;                        // 0x8
    private:
        unsigned char m_unmodelledC[0x30 - 0xC];

        CD2_LAYOUT_CHECKS(cDynamicBodyInteractionData,
            CD2_SIZE(cDynamicBodyInteractionData, 0x30)
            CD2_OFFSET(cDynamicBodyInteractionData, m_nSubItem, 8))
    };
}

#endif // PHYSICS_CDYNAMICBODYINTERACTIONDATA_H
