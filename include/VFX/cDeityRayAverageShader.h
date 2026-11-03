// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// psDeityRayAverage; vsDeityRayAverage.
// Constructor 0x82792260 installs the singleton at 0x838010fc.
// Its callback getter 0x82792250 returns 0x827921E8; instance size is 0x64.
#ifndef VFX_CDEITYRAYAVERAGESHADER_H
#define VFX_CDEITYRAYAVERAGESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRayAverageShader : public cShader
    {
    public:
        static cDeityRayAverageShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRayAverageShader, CD2_SIZE(cDeityRayAverageShader, 0x64))
    };
}
#endif
