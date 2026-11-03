// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; HEMISPHERICAL;MULTIPLICATIVE_BLEND; psSphericalDecal.
// Constructor 0x827a6058 installs the singleton at 0x8380119c.
// Its callback getter 0x827a6048 returns 0x827A5FE0; instance size is 0x64.
#ifndef VFX_CHEMISPHERICALDECALMULTIPLICATIVESHADER_H
#define VFX_CHEMISPHERICALDECALMULTIPLICATIVESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cHemisphericalDecalMultiplicativeShader : public cShader
    {
    public:
        static cHemisphericalDecalMultiplicativeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cHemisphericalDecalMultiplicativeShader, CD2_SIZE(cHemisphericalDecalMultiplicativeShader, 0x64))
    };
}
#endif
