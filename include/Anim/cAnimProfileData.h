// STAND-IN: Burn declares this field-less interface and its profile-taking constructor.
// CD2's concrete profile-data base subobjects have one virtual slot and occupy four bytes.
#ifndef ANIM_CANIMPROFILEDATA_H
#define ANIM_CANIMPROFILEDATA_H
#include "rws/attributes.h"
namespace Anim
{
    class cSpecificAnimationProfile;
    class cAnimProfileData
    {
    public:
        cAnimProfileData(cSpecificAnimationProfile &);
        virtual void HandleAttributeData(cSpecificAnimationProfile &, const RWS::CAttributePacket &) = 0;
        CD2_LAYOUT_CHECKS(cAnimProfileData, CD2_SIZE(cAnimProfileData, 4))
    };
}
#endif
