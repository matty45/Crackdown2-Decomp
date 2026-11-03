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
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x2C];
        CD2_LAYOUT_CHECKS(cProfileDataSprint,
            CD2_SIZE(cProfileDataSprint, 0x30)
            CD2_OFFSET(cProfileDataSprint, m_unmodelledData4, 4))
    };
}
#endif
