// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsDeityRayBlurOcclusion; FILTER_WIDTH=9;RADIUS_SCALE=1;AMPLITUDE=1; psDeityRayBlurOcclusion.
// Constructor 0x82791f18 installs the singleton at 0x838010f4.
// Its callback getter 0x82791f08 returns 0x82791EA0; instance size is 0x64.
#ifndef VFX_CDEITYRAYBLUROCCLUSIONSHADER_H
#define VFX_CDEITYRAYBLUROCCLUSIONSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRayBlurOcclusionShader : public cShader
    {
    public:
        static cDeityRayBlurOcclusionShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRayBlurOcclusionShader, CD2_SIZE(cDeityRayBlurOcclusionShader, 0x64))
    };
}
#endif
