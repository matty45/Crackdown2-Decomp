// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsSphericalDecal; PLANAR;MULTIPLICATIVE_BLEND; psSphericalDecal.
// Constructor 0x827a5d08 installs the singleton at 0x83801194.
// Its callback getter 0x827a5cf8 returns 0x827A5C90; instance size is 0x64.
#ifndef VFX_CPLANARDECALMULTIPLICATIVESHADER_H
#define VFX_CPLANARDECALMULTIPLICATIVESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cPlanarDecalMultiplicativeShader : public cShader
    {
    public:
        static cPlanarDecalMultiplicativeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cPlanarDecalMultiplicativeShader, CD2_SIZE(cPlanarDecalMultiplicativeShader, 0x64))
    };
}
#endif
