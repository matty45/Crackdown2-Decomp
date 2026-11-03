// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// PassThroughPS; PassThroughVS.
// Constructor 0x82799cf8 installs the singleton at 0x8380114c.
// Its callback getter 0x82799ce8 returns 0x82799C80; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMESPASSTHROUGHSHADER_H
#define VFX_CNOISEVOLUMESPASSTHROUGHSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumesPassThroughShader : public cShader
    {
    public:
        static cNoiseVolumesPassThroughShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumesPassThroughShader, CD2_SIZE(cNoiseVolumesPassThroughShader, 0x64))
    };
}
#endif
