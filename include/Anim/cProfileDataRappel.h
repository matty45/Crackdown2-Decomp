// STAND-IN: cProfileDataRappel is named by cAnimHandlerRappel.h.
// CD2 0x824EF2A0 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x40. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATARAPPEL_H
#define ANIM_CPROFILEDATARAPPEL_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataRappel : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
        CD2_LAYOUT_CHECKS(cProfileDataRappel,
            CD2_SIZE(cProfileDataRappel, 0x4))
    };
}
#endif
