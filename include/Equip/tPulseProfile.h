// STAND-IN: Burn/RuffKing names. CD2 constructor 8260FEA8 and attributes
// 8260FFA8 independently establish this complete profile at prototype offset3E0.
#ifndef EQUIP_TPULSEPROFILE_H
#define EQUIP_TPULSEPROFILE_H
#include "Equip/tPulseTargetProfile.h"
#include "Damage/damage_types.h"
namespace Equip
{
    struct tPulseProfile
    {
        tPulseTargetProfile aTargetProfiles[4];
        float fPulseDistance;
        float fPulseConeAngle;
        float fPulseDuration;
        float fPulseDamage;
        Damage::eDamageType nDamageType;
        Damage::eDamageActivator nDamageActivator;
        int nPulseVFXID;
        bool bVFXTrack;
        bool bVFXScale;
        CD2_LAYOUT_CHECKS(tPulseProfile,
            CD2_SIZE(tPulseProfile, 0x40)
            CD2_OFFSET(tPulseProfile, aTargetProfiles, 0)
            CD2_OFFSET(tPulseProfile, fPulseDistance, 0x20)
            CD2_OFFSET(tPulseProfile, fPulseConeAngle, 0x24)
            CD2_OFFSET(tPulseProfile, fPulseDuration, 0x28)
            CD2_OFFSET(tPulseProfile, fPulseDamage, 0x2C)
            CD2_OFFSET(tPulseProfile, nDamageType, 0x30)
            CD2_OFFSET(tPulseProfile, nDamageActivator, 0x34)
            CD2_OFFSET(tPulseProfile, nPulseVFXID, 0x38)
            CD2_OFFSET(tPulseProfile, bVFXTrack, 0x3C)
            CD2_OFFSET(tPulseProfile, bVFXScale, 0x3D))
    };
}
#endif
