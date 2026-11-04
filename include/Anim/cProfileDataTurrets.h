// STAND-IN: cProfileDataTurrets is named by cAnimHandlerTurrets.h.
// CD2 0x8250EF48 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x48. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATATURRETS_H
#define ANIM_CPROFILEDATATURRETS_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataTurrets : public cAnimProfileData
    {
    public:
        // __forceinline: CD2 inlines it into the profile's factory.
        __forceinline cProfileDataTurrets(cSpecificAnimationProfile &profile) : cAnimProfileData(profile) {}
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x8];
        CD2_LAYOUT_CHECKS(cProfileDataTurrets,
            CD2_SIZE(cProfileDataTurrets, 0xC)
            CD2_OFFSET(cProfileDataTurrets, m_unmodelledData4, 4))
    };
}
#endif
