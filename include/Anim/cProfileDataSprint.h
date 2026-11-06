// STAND-IN: cProfileDataSprint is named by cAnimHandlerSprint.h.
// CD2 0x82521958 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x6C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATASPRINT_H
#define ANIM_CPROFILEDATASPRINT_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataSprint : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataSprint(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        // RuffKing names and offsets; CD2 0x825218B0 reads m_fSprintBargeHitTime.
        virtual float RetSprintBargeHitTime() const;
        float m_fSprintMinPlaybackSpeed;
        float m_fSprintMaxPlaybackSpeed;
        float m_fSyncToGroundSpeed;
        bool m_bSyncToGround;
    private:
        float m_fSprintBargeHitTime;
        float m_fBumpWeight[6];
        CD2_LAYOUT_CHECKS(cProfileDataSprint,
            CD2_SIZE(cProfileDataSprint, 0x30)
            CD2_OFFSET(cProfileDataSprint, m_fSprintBargeHitTime, 0x14))
    };
}
#endif
