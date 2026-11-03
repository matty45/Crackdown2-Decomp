// STAND-IN: cProfileDataNPCBarge is named by cAnimHandlerNPCBarge.h.
// CD2 0x824EB030 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x50. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATANPCBARGE_H
#define ANIM_CPROFILEDATANPCBARGE_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataNPCBarge : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x10];
        CD2_LAYOUT_CHECKS(cProfileDataNPCBarge,
            CD2_SIZE(cProfileDataNPCBarge, 0x14)
            CD2_OFFSET(cProfileDataNPCBarge, m_unmodelledData4, 4))
    };
}
#endif
