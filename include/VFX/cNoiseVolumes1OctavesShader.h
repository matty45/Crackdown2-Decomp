// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// NoiseVS; NUM_OCTAVES=1; NoisePS.
// Constructor 0x827994b0 installs the singleton at 0x83801138.
// Its callback getter 0x827994a0 returns 0x82799438; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMES1OCTAVESSHADER_H
#define VFX_CNOISEVOLUMES1OCTAVESSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumes1OctavesShader : public cShader
    {
    public:
        static cNoiseVolumes1OctavesShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumes1OctavesShader, CD2_SIZE(cNoiseVolumes1OctavesShader, 0x64))
    };
}
#endif
