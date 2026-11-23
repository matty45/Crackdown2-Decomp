// STAND-IN: descriptive name ours, from CD2's beacon-explosion shader helper.
// Constructor 0x82805148 uses PassThroughAlphaPS/PassThroughVS from
// shader_PostPro.fx, installs table 0x821553C4 and singleton 0x83801534.
// Slot 1 at 0x82805138 returns reload callback 0x828050D0; size 0x64.
#ifndef VFX_CBEACONEXPLOSIONPASSTHROUGHSHADER_H
#define VFX_CBEACONEXPLOSIONPASSTHROUGHSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cBeaconExplosionPassThroughShader : public cShader
    {
    public:
        static cBeaconExplosionPassThroughShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cBeaconExplosionPassThroughShader,
            CD2_SIZE(cBeaconExplosionPassThroughShader, 0x64))
    };
}
#endif
