// STAND-IN: descriptive name ours, from CD2 shader entries RadialBlurPS / PassThroughVS.
// Constructor 0x82797630 installs the singleton at 0x83801128 and links at +0x60.
// Getter 0x82797550 returns callback 0x827974E8; instance size is 0x64.
#ifndef VFX_CGODRAYSRADIALBLURSHADER_H
#define VFX_CGODRAYSRADIALBLURSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGodRaysRadialBlurShader : public cShader
    {
    public:
        static cGodRaysRadialBlurShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGodRaysRadialBlurShader, CD2_SIZE(cGodRaysRadialBlurShader, 0x64))
    };
}
#endif
