// STAND-IN: RuffKing's names and member order; CD2 constructor 0x82487458
// initializes the vector at +0x90, safe pointer at +0xA0 and FOV at +0xB0
// within cTRCamLookAtStart. The aligned aggregate occupies 0x30 bytes.
#ifndef AI_TTCAMCUTPARAMS_H
#define AI_TTCAMCUTPARAMS_H
#include "fun_runtime/vec3.h"
#include "fun_runtime/safedeletablepointer.h"
#include "gom/game_base.h"
namespace AI
{
    struct tTCamCutParams
    {
        Fun_Runtime::Vec3 vLookAt;
        Fun_Runtime::cSafeDeletablePointer<cGameBase> pObjectToTrack;
        float fFOV;
        CD2_LAYOUT_CHECKS(tTCamCutParams,
            CD2_SIZE(tTCamCutParams, 0x30)
            CD2_OFFSET(tTCamCutParams, vLookAt, 0)
            CD2_OFFSET(tTCamCutParams, pObjectToTrack, 0x10)
            CD2_OFFSET(tTCamCutParams, fFOV, 0x20))
    };
}
#endif
