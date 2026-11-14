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
        // CD2 table 0x82015480 extends the inherited interface at these slots.
        virtual void vf427();
        virtual void vf428();
        virtual void vf429();
        virtual void vf430();
        virtual void vf431();

        // CD2's cluster and shrapnel script-host tables share 0x82619670;
        // cGrenade's corresponding slot holds 0x8261DFC0.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
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
        // CD2: cExplosiveGrenade's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void vf276(); // 276: 0x82380B90
        virtual void vf277(); // 277: 0x8261DA58
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288E730
    private:
        CD2_LAYOUT_CHECKS(cExplosiveGrenade, CD2_SIZE(cExplosiveGrenade, 0x9D0))

    public:
        // CD2 table 0x82015480 differs from cGrenade at these inherited slots.
        virtual Fun_Runtime::RetVal Term(); // slot 6: 0x8229DF90
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // slot 18: 0x8261D5C0
        virtual void Launched(cGameBase *pAttacker); // slot 406: 0x8261D628
        virtual void vf408(); // slot 408: 0x8261D490
        virtual void vf415(); // slot 415: 0x8261DAD0
        virtual void vf416(); // slot 416: 0x8261D6A8
        virtual void vf419(); // slot 419: 0x8261D740
        virtual void vf423(); // slot 423: 0x8261D6E8
        virtual void vf424(); // slot 424: 0x8261DBC8
        virtual void vf425(); // slot 425: 0x8261DC90
    };
}
#endif
