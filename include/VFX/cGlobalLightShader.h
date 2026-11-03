// STAND-IN: descriptive name ours, from CD2 shader entries vsGlobalLight / psGlobalLight.
// Constructor 0x82802408 installs the singleton at 0x83801530 and links at +0x60.
// Getter 0x828021F8 returns callback 0x82802190; instance size is 0x64.
#ifndef VFX_CGLOBALLIGHTSHADER_H
#define VFX_CGLOBALLIGHTSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGlobalLightShader : public cShader
    {
    public:
        static cGlobalLightShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGlobalLightShader, CD2_SIZE(cGlobalLightShader, 0x64))
    };
}
#endif
