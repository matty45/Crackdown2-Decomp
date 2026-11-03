// STAND-IN: descriptive name ours, from CD2 shader entries RestoreDepthPS / PassThroughVS.
// Constructor 0x82796FC8 installs the singleton at 0x83801120 and links at +0x60.
// Getter 0x82796BE8 returns callback 0x82796B80; instance size is 0x64.
#ifndef VFX_CGODRAYSRESTOREDEPTHSHADER_H
#define VFX_CGODRAYSRESTOREDEPTHSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGodRaysRestoreDepthShader : public cShader
    {
    public:
        static cGodRaysRestoreDepthShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGodRaysRestoreDepthShader, CD2_SIZE(cGodRaysRestoreDepthShader, 0x64))
    };
}
#endif
