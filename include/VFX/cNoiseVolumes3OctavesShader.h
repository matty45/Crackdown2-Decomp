// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// NoiseVS; NUM_OCTAVES=3; NoisePS.
// Constructor 0x82799800 installs the singleton at 0x83801140.
// Its callback getter 0x827997f0 returns 0x82799788; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMES3OCTAVESSHADER_H
#define VFX_CNOISEVOLUMES3OCTAVESSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumes3OctavesShader : public cShader
    {
    public:
        static cNoiseVolumes3OctavesShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumes3OctavesShader, CD2_SIZE(cNoiseVolumes3OctavesShader, 0x64))
    };
}
#endif
