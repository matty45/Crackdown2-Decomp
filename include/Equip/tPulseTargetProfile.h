// Reference field names; CD2's pulse attributes use pairs of floats, stride 8.
#ifndef EQUIP_TPULSETARGETPROFILE_H
#define EQUIP_TPULSETARGETPROFILE_H
#include "cd2/layout.h"
namespace Equip
{
    struct tPulseTargetProfile
    {
        float fImpulse;
        float fImpulseDirOffsetY;
        CD2_LAYOUT_CHECKS(tPulseTargetProfile,
            CD2_SIZE(tPulseTargetProfile, 8)
            CD2_OFFSET(tPulseTargetProfile, fImpulse, 0)
            CD2_OFFSET(tPulseTargetProfile, fImpulseDirOffsetY, 4))
    };
}
#endif
