// STAND-IN: cDamageProfileData is named by cDamageHandler.h.
// CD2 0x824F7C18 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x8C. Only the interface is recovered here.
#ifndef ANIM_CDAMAGEPROFILEDATA_H
#define ANIM_CDAMAGEPROFILEDATA_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cDamageProfileData : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cDamageProfileData(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x4C];
        CD2_LAYOUT_CHECKS(cDamageProfileData,
            CD2_SIZE(cDamageProfileData, 0x50)
            CD2_OFFSET(cDamageProfileData, m_unmodelledData4, 4))
    };
}
#endif
