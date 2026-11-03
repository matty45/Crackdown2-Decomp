// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; SPHERICAL; psSphericalDecal.
// Constructor 0x827a5810 installs the singleton at 0x83801188.
// Its callback getter 0x827a5800 returns 0x827A5798; instance size is 0x64.
#ifndef VFX_CSPHERICALDECALSHADER_H
#define VFX_CSPHERICALDECALSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cSphericalDecalShader : public cShader
    {
    public:
        static cSphericalDecalShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cSphericalDecalShader, CD2_SIZE(cSphericalDecalShader, 0x64))
    };
}
#endif
