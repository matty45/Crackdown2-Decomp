// STAND-IN: cProfileDataReaperPropAttack is named by cAnimHandlerReaperPropAttack.h.
// CD2 0x824EC780 forwards to this base at 0x3C; the verified registrar gives
// the complete profile size 0x44. Only the interface is recovered here.
#ifndef ANIM_CPROFILEDATAREAPERPROPATTACK_H
#define ANIM_CPROFILEDATAREAPERPROPATTACK_H
#include "Anim/cAnimProfileData.h"
namespace Anim
{
    class cProfileDataReaperPropAttack : public cAnimProfileData
    {
    public:
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelledData4[0x4];
        CD2_LAYOUT_CHECKS(cProfileDataReaperPropAttack,
            CD2_SIZE(cProfileDataReaperPropAttack, 0x8)
            CD2_OFFSET(cProfileDataReaperPropAttack, m_unmodelledData4, 4))
    };
}
#endif
