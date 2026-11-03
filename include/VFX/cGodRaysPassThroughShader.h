// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// PassThroughPS; PassThroughVS.
// Constructor 0x827977d0 installs the singleton at 0x8380112c.
// Its callback getter 0x827977c0 returns 0x82797758; instance size is 0x64.
#ifndef VFX_CGODRAYSPASSTHROUGHSHADER_H
#define VFX_CGODRAYSPASSTHROUGHSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGodRaysPassThroughShader : public cShader
    {
    public:
        static cGodRaysPassThroughShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGodRaysPassThroughShader, CD2_SIZE(cGodRaysPassThroughShader, 0x64))
    };
}
#endif
