// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; HEMISPHERICAL; psSphericalDecal.
// Constructor 0x827a5eb0 installs the singleton at 0x83801198.
// Its callback getter 0x827a5ea0 returns 0x827A5E38; instance size is 0x64.
#ifndef VFX_CHEMISPHERICALDECALSHADER_H
#define VFX_CHEMISPHERICALDECALSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cHemisphericalDecalShader : public cShader
    {
    public:
        static cHemisphericalDecalShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cHemisphericalDecalShader, CD2_SIZE(cHemisphericalDecalShader, 0x64))
    };
}
#endif
