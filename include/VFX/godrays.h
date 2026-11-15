// God-ray console controls: descriptive C++ names ours, from CD2's registrations in
// 0x82797988. "grblock" is described there as "God Rays Cloud Block Factor".
// The callback ABI is Cmd::cConsoleCommand::Add's (context, wide argument string).
#ifndef VFX_GODRAYS_H
#define VFX_GODRAYS_H

namespace VFX
{
    // CD2 0x8309642C, initialized to 2.0 and stored by callback 0x827964B8.
    extern float g_fGodRaysCloudBlockFactor;
    void SetGodRaysCloudBlockFactor(void *context, wchar_t *argument);
    // "grfalloff"; CD2 0x83096428 starts at 1.2, callback 0x827964E8.
    extern float g_fGodRaysFalloffFactor;
    void SetGodRaysFalloffFactor(void *context, wchar_t *argument);
    // "grmagf"; CD2 0x83096424 starts at 0.71, callback 0x82796518.
    extern float g_fGodRaysMagnificationFactor;
    void SetGodRaysMagnificationFactor(void *context, wchar_t *argument);
    // "grraysize"; CD2 0x8309641C starts at 350, callback 0x82796548.
    extern float g_fGodRaysSize;
    void SetGodRaysSize(void *context, wchar_t *argument);
    // "grmode"; CD2 0x83801114 starts at zero, callback 0x827965F0.
    extern int g_nGodRaysMode;
    void SetGodRaysMode(void *context, wchar_t *argument);
    // "grtry"; CD2 0x83801118 starts at zero, callback 0x82796620.
    // Keep the command's own name: the setting's broader purpose is not recovered yet.
    extern int g_nGodRaysTry;
    void SetGodRaysTry(void *context, wchar_t *argument);
}

#endif
