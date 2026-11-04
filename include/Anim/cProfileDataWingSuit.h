// STAND-IN: cProfileDataWingSuit is named by cAnimHandlerWingSuit.h.
// CD2 0x824F3E50 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0xDC. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAWINGSUIT_H
#define ANIM_CPROFILEDATAWINGSUIT_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataWingSuit : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataWingSuit(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x9C];
        CD2_LAYOUT_CHECKS(cProfileDataWingSuit,
            CD2_SIZE(cProfileDataWingSuit, 0xA0)
            CD2_OFFSET(cProfileDataWingSuit, m_unmodelledData4, 4))
    };
}
#endif
