// STAND-IN: descriptive name ours, from CD2 shader entries RestoreDepthPS / PassThroughVS.
// Constructor 0x8279A2C8 installs the singleton at 0x83801150 and links at +0x60.
// Getter 0x82799E88 returns callback 0x82799E20; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMESRESTOREDEPTHSHADER_H
#define VFX_CNOISEVOLUMESRESTOREDEPTHSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumesRestoreDepthShader : public cShader
    {
    public:
        static cNoiseVolumesRestoreDepthShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumesRestoreDepthShader, CD2_SIZE(cNoiseVolumesRestoreDepthShader, 0x64))
    };
}
#endif
