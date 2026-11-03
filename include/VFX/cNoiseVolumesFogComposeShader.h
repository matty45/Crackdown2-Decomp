// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// FogComposePS; PassThroughVS.
// Constructor 0x8279a468 installs the singleton at 0x83801154.
// Its callback getter 0x8279a458 returns 0x8279A3F0; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMESFOGCOMPOSESHADER_H
#define VFX_CNOISEVOLUMESFOGCOMPOSESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumesFogComposeShader : public cShader
    {
    public:
        static cNoiseVolumesFogComposeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumesFogComposeShader, CD2_SIZE(cNoiseVolumesFogComposeShader, 0x64))
    };
}
#endif
