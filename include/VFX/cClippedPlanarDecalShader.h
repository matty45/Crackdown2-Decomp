// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// PLANAR; vsSphericalDecalClipped.
// Constructor 0x827a6550 installs the singleton at 0x838011a8.
// Its callback getter 0x827a6540 returns 0x827A64D8; instance size is 0x64.
#ifndef VFX_CCLIPPEDPLANARDECALSHADER_H
#define VFX_CCLIPPEDPLANARDECALSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cClippedPlanarDecalShader : public cShader
    {
    public:
        static cClippedPlanarDecalShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cClippedPlanarDecalShader, CD2_SIZE(cClippedPlanarDecalShader, 0x64))
    };
}
#endif
