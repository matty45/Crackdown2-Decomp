// STAND-IN: cDeathProfileData is named by cDeathHandler.h.
// CD2 0x824FD700 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x44. Only the interface is recovered here.
#ifndef ANIM_CDEATHPROFILEDATA_H
#define ANIM_CDEATHPROFILEDATA_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cDeathProfileData : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cDeathProfileData(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x4];
        CD2_LAYOUT_CHECKS(cDeathProfileData,
            CD2_SIZE(cDeathProfileData, 0x8)
            CD2_OFFSET(cDeathProfileData, m_unmodelledData4, 4))
    };
}
#endif
