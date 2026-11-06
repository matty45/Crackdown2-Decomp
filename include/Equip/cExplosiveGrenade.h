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
        // CD2 0x8261D220: placement factory.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8261D3F0: restores this class's vtables, then calls cGrenade's destructor.
        virtual ~cExplosiveGrenade();
        // CD2 0x8261D2E0, called by cClusterGrenade's placement factory with only this.
        cExplosiveGrenade();
        // Name and base from RuffKing. CD2: cExplosiveGrenade::MakeNew (0x8261D1B8) allocates 0x390 and calls this
        // constructor (0x821FE7C8), which calls cGrenadePrototype's (0x8261F758).
        class cExplosiveGrenadePrototype : public cGrenade::cGrenadePrototype
        {
        public:
            cExplosiveGrenadePrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled370[0x390 - 0x370];

            CD2_LAYOUT_CHECKS(cExplosiveGrenadePrototype,
                CD2_SIZE(cExplosiveGrenadePrototype, 0x390))
        };

        // CD2 0x8261D210: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosiveGrenadeClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    private:
        unsigned char m_unmodelled9C4[0x9D0 - 0x9C4];
        CD2_LAYOUT_CHECKS(cExplosiveGrenade, CD2_SIZE(cExplosiveGrenade, 0x9D0))
    };
}
#endif
