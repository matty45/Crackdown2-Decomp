// VFX::cGlobalLightPool (Crackdown 2): STAND-IN, declared only: the pool of global lights and its one instance,
// which Equip::cFlocket returns its light to (cFlocket.cpp). Layout and functions not modelled; the names are ours.
#ifndef VFX_CGLOBALLIGHTPOOL_H
#define VFX_CGLOBALLIGHTPOOL_H

namespace VFX
{
    class cGlobalLight;
    class cGlobalLightPool;
    extern cGlobalLightPool g_GlobalLightPool;
}

#endif // VFX_CGLOBALLIGHTPOOL_H
