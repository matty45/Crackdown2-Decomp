// STAND-IN: descriptive name ours, from CD2's vsDeityRayOcclude/psDeityRayOcclude
// entry names. Constructor 0x82791BD0 installs the singleton at 0x838010EC;
// vtable 0x8214CD58 slot 1 returns ReloadInstance (0x82791B58).
#ifndef VFX_CDEITYRAYOCCLUDESHADER_H
#define VFX_CDEITYRAYOCCLUDESHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRayOccludeShader : public cShader
    {
    public:
        static cDeityRayOccludeShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRayOccludeShader, CD2_SIZE(cDeityRayOccludeShader, 0x64))
    };
}
#endif
