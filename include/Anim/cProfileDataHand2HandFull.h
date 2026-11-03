// STAND-IN: cProfileDataHand2HandFull is named by cAnimHandlerHand2HandFull.h.
// CD2 0x825161F8 forwards to this base at 0x40; the verified registrar gives
// the complete profile size 0x3EE0. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAHAND2HANDFULL_H
#define ANIM_CPROFILEDATAHAND2HANDFULL_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    // The reference's Vec3 arrays require 16-byte alignment; CD2's base adjustment confirms it.
    __declspec(align(16)) class cProfileDataHand2HandFull : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x3E9C];
        CD2_LAYOUT_CHECKS(cProfileDataHand2HandFull,
            CD2_SIZE(cProfileDataHand2HandFull, 0x3EA0)
            CD2_OFFSET(cProfileDataHand2HandFull, m_unmodelledData4, 4))
    };
}
#endif
