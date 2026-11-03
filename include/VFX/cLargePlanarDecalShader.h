// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; PLANAR;LARGE_PLANAR; psSphericalDecal.
// Constructor 0x827a6200 installs the singleton at 0x838011a0.
// Its callback getter 0x827a61f0 returns 0x827A6188; instance size is 0x64.
#ifndef VFX_CLARGEPLANARDECALSHADER_H
#define VFX_CLARGEPLANARDECALSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cLargePlanarDecalShader : public cShader
    {
    public:
        static cLargePlanarDecalShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cLargePlanarDecalShader, CD2_SIZE(cLargePlanarDecalShader, 0x64))
    };
}
#endif
