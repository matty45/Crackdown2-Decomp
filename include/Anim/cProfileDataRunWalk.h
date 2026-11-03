// STAND-IN: cProfileDataRunWalk is named by cAnimHandlerRunWalk.h.
// CD2 0x824F7940 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x1B0. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATARUNWALK_H
#define ANIM_CPROFILEDATARUNWALK_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataRunWalk : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x170];
        CD2_LAYOUT_CHECKS(cProfileDataRunWalk,
            CD2_SIZE(cProfileDataRunWalk, 0x174)
            CD2_OFFSET(cProfileDataRunWalk, m_unmodelledData4, 4))
    };
}
#endif
