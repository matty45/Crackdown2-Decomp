#include "Equip/cGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cSmokeGrenade (Crackdown 2): STAND-IN; base and fields from CD2's placement factory 0x826226D0,
// which inlines the constructor: cGrenade's constructor (0x8261E238), the vtables, then the three fields below. Field names
// from RuffKing (m_pSmokeVFX, m_nSmokeTime_msec, m_bDeleteOnDetonationEnd); the destructor 0x82622878 releases m_pSmokeVFX.
// StaticCreateClass (0x82622790) builds cClass(0x3E8D, "cSmokeGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CSMOKEGRENADE_H
#define EQUIP_CSMOKEGRENADE_H

#include "fun_runtime/class.h"

namespace VFX
{
    class cParticleEffectInstance;
}

namespace Equip
{
    class cSmokeGrenade : public cGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x82622D80).
        // CD2 MakeNew allocates 0x380 and initializes both reference-named fields.
        class cSmokeGrenadePrototype : public cGrenade::cGrenadePrototype
        {
        public:
            // CD2 expands construction into MakeNew; its grenade-prototype base stays out of line.
            __forceinline cSmokeGrenadePrototype(const RWS::CAttributePacket &packet)
                : cGrenadePrototype(packet), m_nMaxSmokeTime_msec(0), m_nSmokeEffectID(-1) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
        protected:
            int m_nMaxSmokeTime_msec;
            int m_nSmokeEffectID;
            CD2_LAYOUT_CHECKS(cSmokeGrenadePrototype,
                CD2_SIZE(cSmokeGrenadePrototype, 0x380)
                CD2_OFFSET(cSmokeGrenadePrototype, m_nMaxSmokeTime_msec, 0x370)
                CD2_OFFSET(cSmokeGrenadePrototype, m_nSmokeEffectID, 0x374))
        };

        // CD2 0x826225D0: registered-class virtual slot 0 reads this class descriptor.
        // __forceinline: CD2's placement factory 0x826226D0 inlines this constructor (base call, every vtable store and
        // the fields); /Ob1 declines a plain inline constructor with this many stores (docs/matching-notes.md, Inlining).
        __forceinline cSmokeGrenade() : m_pSmokeVFX(0), m_nSmokeTime_msec(0), m_bDeleteOnDetonationEnd(false) {}
        // CD2 0x82622878.
        virtual ~cSmokeGrenade();
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826225E0: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x826226C0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD0C70 names placement factory 0x826226d0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSmokeGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    protected:
        VFX::cParticleEffectInstance *m_pSmokeVFX;
        int m_nSmokeTime_msec;
        bool m_bDeleteOnDetonationEnd;

        // CD2: cSmokeGrenade's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x822F4390
        virtual void Slot23(); // 23: 0x82622BB8
        virtual void vf140(); // 140: 0x82622BF8
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8261F5F0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82396118
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x8261DFC0
    protected:
        CD2_LAYOUT_CHECKS(cSmokeGrenade,
            CD2_SIZE(cSmokeGrenade, 0x9D0)
            CD2_OFFSET(cSmokeGrenade, m_pSmokeVFX, 0x9C0)
            CD2_OFFSET(cSmokeGrenade, m_nSmokeTime_msec, 0x9C4)
            CD2_OFFSET(cSmokeGrenade, m_bDeleteOnDetonationEnd, 0x9C8))

    public:
        // CD2 table 0x82124F98 differs from cGrenade at these inherited slots.
        virtual void vf419(); // slot 419: 0x826229A0
        virtual void vf420(); // slot 420: 0x82622AA8
        virtual void vf421(); // slot 421: 0x82622B70
    };
}

#endif // EQUIP_CSMOKEGRENADE_H
