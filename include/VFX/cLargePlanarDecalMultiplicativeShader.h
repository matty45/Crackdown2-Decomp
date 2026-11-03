// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; PLANAR;LARGE_PLANAR;MULTIPLICATIVE_BLEND; psSphericalDecal.
// Constructor 0x827a63a8 installs the singleton at 0x838011a4.
// Its callback getter 0x827a6398 returns 0x827A6330; instance size is 0x64.
#ifndef VFX_CLARGEPLANARDECALMULTIPLICATIVESHADER_H
#define VFX_CLARGEPLANARDECALMULTIPLICATIVESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cLargePlanarDecalMultiplicativeShader : public cShader
    {
    public:
        static cLargePlanarDecalMultiplicativeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cLargePlanarDecalMultiplicativeShader, CD2_SIZE(cLargePlanarDecalMultiplicativeShader, 0x64))
    };
}
#endif
