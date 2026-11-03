// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; SPHERICAL;MULTIPLICATIVE_BLEND; psSphericalDecal.
// Constructor 0x827a59b8 installs the singleton at 0x8380118c.
// Its callback getter 0x827a59a8 returns 0x827A5940; instance size is 0x64.
#ifndef VFX_CSPHERICALDECALMULTIPLICATIVESHADER_H
#define VFX_CSPHERICALDECALMULTIPLICATIVESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cSphericalDecalMultiplicativeShader : public cShader
    {
    public:
        static cSphericalDecalMultiplicativeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cSphericalDecalMultiplicativeShader, CD2_SIZE(cSphericalDecalMultiplicativeShader, 0x64))
    };
}
#endif
