// Method-only STAND-IN, not an allocation layout. The reference
// cExplosionEffect header names StartExplosion; CD2 0x8263C3A8 is called after
// creation/chaining by cExplosionManager::InitiateExplosion (0x8263F228).
// Its collector base and instance fields are not modelled here.
#ifndef EXPLOSIONMANAGER_CEXPLOSIONEFFECT_H
#define EXPLOSIONMANAGER_CEXPLOSIONEFFECT_H
namespace ExplosionManager
{
    class cExplosionEffect
    {
    public:
        void StartExplosion();
    };
}
#endif
