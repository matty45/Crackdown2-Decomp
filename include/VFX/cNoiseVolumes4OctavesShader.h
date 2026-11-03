// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// NoiseVS; NUM_OCTAVES=4; NoisePS.
// Constructor 0x827999a8 installs the singleton at 0x83801144.
// Its callback getter 0x82799998 returns 0x82799930; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMES4OCTAVESSHADER_H
#define VFX_CNOISEVOLUMES4OCTAVESSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumes4OctavesShader : public cShader
    {
    public:
        static cNoiseVolumes4OctavesShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumes4OctavesShader, CD2_SIZE(cNoiseVolumes4OctavesShader, 0x64))
    };
}
#endif
