// STAND-IN: cProfileDataCrouch is named by cAnimHandlerCrouch.h.
// CD2 0x82520A48 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x5C. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATACROUCH_H
#define ANIM_CPROFILEDATACROUCH_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataCrouch : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x1C];
        CD2_LAYOUT_CHECKS(cProfileDataCrouch,
            CD2_SIZE(cProfileDataCrouch, 0x20)
            CD2_OFFSET(cProfileDataCrouch, m_unmodelledData4, 4))
    };
}
#endif
