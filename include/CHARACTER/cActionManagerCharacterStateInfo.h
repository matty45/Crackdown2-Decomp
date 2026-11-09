// STAND-IN: Burn/RuffKing member names/order. CD2's two 0x30-byte animation-parameter objects replace their
// 0x18-byte objects, shifting the later fields by +0x30. Inventory at +0xF0 is confirmed by the character's
// action-manager/state/inventory address chain in 0x8254E980; its primary pointer is read by 0x8254E9A0.
#ifndef CHARACTER_CACTIONMANAGERCHARACTERSTATEINFO_H
#define CHARACTER_CACTIONMANAGERCHARACTERSTATEINFO_H

#include "CHARACTER/cActionManagerCharacterCharacterStateInfoBools.h"
#include "Anim/cAnimationParams.h"
#include "Equip/cCharacterInventory.h"
#include "fun_runtime/safedeletablepointer.h"

namespace Vehicle { class cVehicle; class cVehicleSeat; }
namespace PHYSICS { class cDynamicBody; }

namespace CHARACTER
{
    class cActionManagerCharacterStateInfo : public cActionManagerCharacterCharacterStateInfoBools
    {
    public:
        cActionManagerCharacterStateInfo();
        ~cActionManagerCharacterStateInfo();
        Equip::cCharacterInventory &RetInventory() { return m_Inventory; }
    private:
        unsigned char m_nDamageLocation;
        unsigned char m_nDamageDirection;
        unsigned char m_nDamageType;
        unsigned int m_nNextFlinchFrame;
        unsigned char m_Rand;
        unsigned char m_nSeatID;
        unsigned char m_nVehiclePosType;
        bool m_bIsPropMedCarryHigh;
        Anim::cAnimationParams m_MainGenericParams;
        Anim::cAnimationParams m_UpperGenericParams;
        Vehicle::cVehicleSeat *m_pSeat;
        Fun_Runtime::cSafeDeletablePointer<Vehicle::cVehicle> m_pVehicle;
        int m_ObjectHandle;
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pCarriedObject;
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pStandingOn;
        Fun_Runtime::cSafeDeletablePointer<Equip::cEquipment> m_pInteractionEquipment;
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pInteractionProp;
        char m_nPropAttatchmentIndex;
        float m_fMaxJumpHeight;
        bool m_bWasStunned;
        float m_fCanVaultTime;
        float m_fInitRushVel;
        bool m_bLaunchPadLaunch;
        float m_fWingSuitLRAng;
        float m_fWingSuitFBAng;
        Equip::cCharacterInventory m_Inventory;
        CD2_LAYOUT_CHECKS(cActionManagerCharacterStateInfo,
            CD2_SIZE(cActionManagerCharacterStateInfo, 0x480)
            CD2_OFFSET(cActionManagerCharacterStateInfo, m_nDamageLocation, 4)
            CD2_OFFSET(cActionManagerCharacterStateInfo, m_MainGenericParams, 0x10)
            CD2_OFFSET(cActionManagerCharacterStateInfo, m_UpperGenericParams, 0x40)
            CD2_OFFSET(cActionManagerCharacterStateInfo, m_pVehicle, 0x74)
            CD2_OFFSET(cActionManagerCharacterStateInfo, m_Inventory, 0xF0))
    };
}
#endif
