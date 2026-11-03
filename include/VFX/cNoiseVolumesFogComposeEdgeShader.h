// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// FogComposeEdgePS; PassThroughVS.
// Constructor 0x8279a608 installs the singleton at 0x83801158.
// Its callback getter 0x8279a5f8 returns 0x8279A590; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMESFOGCOMPOSEEDGESHADER_H
#define VFX_CNOISEVOLUMESFOGCOMPOSEEDGESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumesFogComposeEdgeShader : public cShader
    {
    public:
        static cNoiseVolumesFogComposeEdgeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumesFogComposeEdgeShader, CD2_SIZE(cNoiseVolumesFogComposeEdgeShader, 0x64))
    };
}
#endif
