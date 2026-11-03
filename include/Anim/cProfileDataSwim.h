// STAND-IN: cProfileDataSwim is named by cAnimHandlerSwim.h.
// CD2 0x82523CF0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x4C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATASWIM_H
#define ANIM_CPROFILEDATASWIM_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataSwim : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0xC];
        CD2_LAYOUT_CHECKS(cProfileDataSwim,
            CD2_SIZE(cProfileDataSwim, 0x10)
            CD2_OFFSET(cProfileDataSwim, m_unmodelledData4, 4))
    };
}
#endif
