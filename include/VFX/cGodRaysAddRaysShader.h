// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// AddRaysPS; PassThroughVS.
// Constructor 0x82796a58 installs the singleton at 0x8380111c.
// Its callback getter 0x82796a48 returns 0x827969E0; instance size is 0x64.
#ifndef VFX_CGODRAYSADDRAYSSHADER_H
#define VFX_CGODRAYSADDRAYSSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cGodRaysAddRaysShader : public cShader
    {
    public:
        static cGodRaysAddRaysShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cGodRaysAddRaysShader, CD2_SIZE(cGodRaysAddRaysShader, 0x64))
    };
}
#endif
