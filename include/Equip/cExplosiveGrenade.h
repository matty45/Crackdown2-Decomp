// STAND-IN: RuffKing cExplosiveGrenade derives from cGrenade and cExplosionCallback.
// CD2 constructor 0x8261D2E0 calls cGrenade's constructor and installs the callback
// at +0x9C0. Descriptor 0x8261D248 gives size 0x9D0; remaining data is opaque.
#ifndef EQUIP_CEXPLOSIVEGRENADE_H
#define EQUIP_CEXPLOSIVEGRENADE_H
#include "Equip/cGrenade.h"
#include "ExplosionManager/cExplosionCallback.h"
namespace Equip
{
    class cExplosiveGrenade : public cGrenade, public ExplosionManager::cExplosionCallback
    {
    public:
        // CD2 0x8261D3F0: restores this class's vtables, then calls cGrenade's destructor.
        virtual ~cExplosiveGrenade();
        // CD2 0x8261D2E0, called by cClusterGrenade's placement factory with only this.
        cExplosiveGrenade();
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cExplosiveGrenadePrototype : public cGrenade::cGrenadePrototype {};

        // CD2 0x8261D210: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosiveGrenadeClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
    private:
        unsigned char m_unmodelled9C4[0x9D0 - 0x9C4];
        CD2_LAYOUT_CHECKS(cExplosiveGrenade, CD2_SIZE(cExplosiveGrenade, 0x9D0))
    };
}
#endif
