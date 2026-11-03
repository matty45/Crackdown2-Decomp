// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// EdgeDetectPS; PassThroughVS.
// Constructor 0x8279a7a8 installs the singleton at 0x8380115c.
// Its callback getter 0x8279a798 returns 0x8279A730; instance size is 0x64.
#ifndef VFX_CNOISEVOLUMESEDGEDETECTSHADER_H
#define VFX_CNOISEVOLUMESEDGEDETECTSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cNoiseVolumesEdgeDetectShader : public cShader
    {
    public:
        static cNoiseVolumesEdgeDetectShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cNoiseVolumesEdgeDetectShader, CD2_SIZE(cNoiseVolumesEdgeDetectShader, 0x64))
    };
}
#endif
