// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// NoiseVS; NUM_OCTAVES=2; NoisePS.
// Constructor 0x82799658 installs the singleton at 0x8380113c.
// Its callback getter 0x82799648 returns 0x827995E0; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMES2OCTAVESSHADER_H
#define VFX_CNOISEVOLUMES2OCTAVESSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumes2OctavesShader : public cShader
    {
    public:
        static cNoiseVolumes2OctavesShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumes2OctavesShader, CD2_SIZE(cNoiseVolumes2OctavesShader, 0x64))
    };
}
#endif
