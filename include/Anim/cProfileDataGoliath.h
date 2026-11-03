// STAND-IN: cProfileDataGoliath is named by cAnimHandlerGoliath.h.
// CD2 0x824ED020 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x4C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAGOLIATH_H
#define ANIM_CPROFILEDATAGOLIATH_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataGoliath : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0xC];
        CD2_LAYOUT_CHECKS(cProfileDataGoliath,
            CD2_SIZE(cProfileDataGoliath, 0x10)
            CD2_OFFSET(cProfileDataGoliath, m_unmodelledData4, 4))
    };
}
#endif
