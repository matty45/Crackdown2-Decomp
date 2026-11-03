// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// psDeityRay; vsDeityRay.
// Constructor 0x82791d78 installs the singleton at 0x838010f0.
// Its callback getter 0x82791d68 returns 0x82791D00; instance size is 0x64.
#ifndef VFX_CDEITYRAYSHADER_H
#define VFX_CDEITYRAYSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRayShader : public cShader
    {
    public:
        static cDeityRayShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRayShader, CD2_SIZE(cDeityRayShader, 0x64))
    };
}
#endif
