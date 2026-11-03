// STAND-IN: cStunnedProfileData is named by cStunnedHandler.h.
// CD2 0x825004C8 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x44. Only the interface is recovered here.
#ifndef ANIM_CSTUNNEDPROFILEDATA_H
#define ANIM_CSTUNNEDPROFILEDATA_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cStunnedProfileData : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x4];
        CD2_LAYOUT_CHECKS(cStunnedProfileData,
            CD2_SIZE(cStunnedProfileData, 0x8)
            CD2_OFFSET(cStunnedProfileData, m_unmodelledData4, 4))
    };
}
#endif
