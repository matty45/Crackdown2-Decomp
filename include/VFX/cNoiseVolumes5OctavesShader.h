// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// NoiseVS; NUM_OCTAVES=5; NoisePS.
// Constructor 0x82799b50 installs the singleton at 0x83801148.
// Its callback getter 0x82799b40 returns 0x82799AD8; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMES5OCTAVESSHADER_H
#define VFX_CNOISEVOLUMES5OCTAVESSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumes5OctavesShader : public cShader
    {
    public:
        static cNoiseVolumes5OctavesShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumes5OctavesShader, CD2_SIZE(cNoiseVolumes5OctavesShader, 0x64))
    };
}
#endif
