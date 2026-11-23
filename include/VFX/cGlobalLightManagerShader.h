// STAND-IN: descriptive name ours, from the shader constructed by
// cGlobalLightManager's object. CD2 0x827FB048 uses vsGlobalLight/psGlobalLight
// from shader_globallights.fx and installs table 0x821551D0.
// Slot 1 at 0x827FB038 returns the reload callback at 0x82274520.
#ifndef VFX_CGLOBALLIGHTMANAGERSHADER_H
#define VFX_CGLOBALLIGHTMANAGERSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGlobalLightManagerShader : public cShader
    {
    public:
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGlobalLightManagerShader, CD2_SIZE(cGlobalLightManagerShader, 0x64))
    };
}
#endif
