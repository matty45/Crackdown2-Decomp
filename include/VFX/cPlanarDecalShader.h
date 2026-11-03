// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; PLANAR; psSphericalDecal.
// Constructor 0x827a5b60 installs the singleton at 0x83801190.
// Its callback getter 0x827a5b50 returns 0x827A5AE8; instance size is 0x64.
#ifndef VFX_CPLANARDECALSHADER_H
#define VFX_CPLANARDECALSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cPlanarDecalShader : public cShader
    {
    public:
        static cPlanarDecalShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cPlanarDecalShader, CD2_SIZE(cPlanarDecalShader, 0x64))
    };
}
#endif
