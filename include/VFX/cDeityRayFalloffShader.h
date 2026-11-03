// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// psDeityRayFalloff; vsDeityRayFalloff.
// Constructor 0x827920c0 installs the singleton at 0x838010f8.
// Its callback getter 0x827920b0 returns 0x82792048; instance size is 0x64.
#ifndef VFX_CDEITYRAYFALLOFFSHADER_H
#define VFX_CDEITYRAYFALLOFFSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRayFalloffShader : public cShader
    {
    public:
        static cDeityRayFalloffShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRayFalloffShader, CD2_SIZE(cDeityRayFalloffShader, 0x64))
    };
}
#endif
