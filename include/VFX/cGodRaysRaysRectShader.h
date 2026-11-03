// STAND-IN: descriptive name ours, from CD2 shader entries RaysRectPS / RaysRectVS.
// Constructor 0x827973C0 installs the singleton at 0x83801124 and links at +0x60.
// Getter 0x82797158 returns callback 0x827970F0; instance size is 0x64.
#ifndef VFX_CGODRAYSRAYSRECTSHADER_H
#define VFX_CGODRAYSRAYSRECTSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGodRaysRaysRectShader : public cShader
    {
    public:
        static cGodRaysRaysRectShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGodRaysRaysRectShader, CD2_SIZE(cGodRaysRaysRectShader, 0x64))
    };
}
#endif
