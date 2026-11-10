// STAND-IN: cProfileDataPropCarryNPC is named by cAnimHandlerNPCPropCarryFull.h.
// CD2 0x824EB900 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x4C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAPROPCARRYNPC_H
#define ANIM_CPROFILEDATAPROPCARRYNPC_H
#include "Anim/cAnimProfileData.h"
#include "fun_runtime/class.h"
namespace Anim
{
    class cProfileDataPropCarryNPC : public cAnimProfileData
    {
    public:
        // Burn's member names; CD2 0x824EB840 copies CONST_FLOAT_1 separately
        // into the three fields while inlining this constructor into the factory.
        __forceinline cProfileDataPropCarryNPC(cSpecificAnimationProfile &profile)
            : cAnimProfileData(profile), m_fStepRoundMinPlaybackRate(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1),
              m_fStepRoundMaxPlaybackRate(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1),
              m_fStepRoundRotationSpeed(Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        float m_fStepRoundMinPlaybackRate;
        float m_fStepRoundMaxPlaybackRate;
        float m_fStepRoundRotationSpeed;
        CD2_LAYOUT_CHECKS(cProfileDataPropCarryNPC,
            CD2_SIZE(cProfileDataPropCarryNPC, 0x10)
            CD2_OFFSET(cProfileDataPropCarryNPC, m_fStepRoundMinPlaybackRate, 4)
            CD2_OFFSET(cProfileDataPropCarryNPC, m_fStepRoundMaxPlaybackRate, 8)
            CD2_OFFSET(cProfileDataPropCarryNPC, m_fStepRoundRotationSpeed, 0xC))
    };
}
#endif
