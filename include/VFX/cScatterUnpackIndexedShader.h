// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsScatterUnpack; INDEXED; psScatterUnpack.
// Constructor 0x827aa728 installs the singleton at 0x838011b4.
// Its callback getter 0x827aa718 returns 0x827AA6B0; instance size is 0x64.
#ifndef VFX_CSCATTERUNPACKINDEXEDSHADER_H
#define VFX_CSCATTERUNPACKINDEXEDSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cScatterUnpackIndexedShader : public cShader
    {
    public:
        static cScatterUnpackIndexedShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cScatterUnpackIndexedShader, CD2_SIZE(cScatterUnpackIndexedShader, 0x64))
    };
}
#endif
