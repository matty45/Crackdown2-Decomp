#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/vec3.h"
// Equip::cChainGun (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWFirearm: CD2's inheritance registrar names it, and the destructor 0x82616780 calls cCWFirearm's (0x82617EB8).
// StaticCreateClass (0x82616690) builds cClass(0x13266, "cChainGun", 0xAC0); 0xAC0 is the size its registrar gives.
#ifndef EQUIP_CCHAINGUN_H
#define EQUIP_CCHAINGUN_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cChainGun : public cCWFirearm
    {
    public:
        // Inline: CD2's placement factory (0x826165B8) calls cCWFirearm's (0x821F0768) constructor, then stores this class's vptrs.
        __forceinline cChainGun() : m_fBarrelSpeed(0.0f), m_fExtendTrans(0.0f) {}
        // Name and base from RuffKing. CD2's MakeNew (0x82616550) allocates 0x780 and calls the constructor
        // (0x82616EB0) out of line, which calls cCWFirearmPrototype's (0x82618660); own fields are not recovered.
        struct tChainGunLevelData
        {
            float m_fMinDamage;
            float m_fMaxDamage;
            float m_fMinDuration;
            float m_fMaxDuration;
        };
        // Members in RuffKing's order and names, 0x30 later than there (CD2's cCWFirearmPrototype ends at 0x6E0); the
        // constructor 0x82616EB0 initializes every one at these offsets.
        class cChainGunPrototype : public cCWFirearm::cCWFirearmPrototype
        {
        public:
            cChainGunPrototype(const RWS::CAttributePacket &);

            unsigned char m_nCaseFrameID;
            unsigned char m_nCaseExFrameID;
            unsigned char m_nBarrelFrameID;
            tChainGunLevelData m_aChainGunLevelData[5];
            float m_fMaxAngVel;
            float m_fMaxAngVelRecip;
            float m_fFiringAcc;
            float m_fIdleAcc;
            float m_fReloadAcc;
            float m_fExtendFraction;
            float m_fExtendSpeed;
            float m_fMaxExtend;
            Fun_Runtime::Vec3 m_vecBarrelAxis;
            bool m_bAnimate;

        private:
            CD2_LAYOUT_CHECKS(cChainGunPrototype,
                CD2_SIZE(cChainGunPrototype, 0x780)
                CD2_OFFSET(cChainGunPrototype, m_nCaseFrameID, 0x6E0)
                CD2_OFFSET(cChainGunPrototype, m_aChainGunLevelData, 0x6E4)
                CD2_OFFSET(cChainGunPrototype, m_fMaxAngVel, 0x734)
                CD2_OFFSET(cChainGunPrototype, m_fMaxAngVelRecip, 0x738)
                CD2_OFFSET(cChainGunPrototype, m_fMaxExtend, 0x750)
                CD2_OFFSET(cChainGunPrototype, m_vecBarrelAxis, 0x760)
                CD2_OFFSET(cChainGunPrototype, m_bAnimate, 0x770))
        };
        const cChainGunPrototype *RetChainGunPrototype() const
        {
            return static_cast<const cChainGunPrototype *>(m_pPrototype);
        }

        // CD2 0x826165A8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82616780.
        virtual ~cChainGun();
        // CD2 spawning initializer 0x82FCE608 names placement factory 0x826165b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcChainGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // RuffKing's names. CD2 0x82616870 (called by TickUpdate with its time step).
        void Animate(float fDeltaTime_secs);
        // CD2 0x82616D98: the owner's firearms level selects the entry, the first without a character owner.
        const tChainGunLevelData *RetLevelData() const;

        float m_fBarrelSpeed;                      // 0xAB0 (RuffKing's names)
        float m_fExtendTrans;                      // 0xAB4
        unsigned char m_unmodelledAB8[0xAC0 - 0xAB8];

        // CD2: cChainGun's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void TickUpdate(float fDeltaTime); // 23: 0x82616828
        // CD2 0x826164E0 / 0x826164F0; the cBody (+0xF0) and cReplicatedClass (+0x4E0) tables reach them through
        // thunks 0x82617C88/0x82617C90 and 0x82617CB8/0x82617CC8.
        virtual Fun_Runtime::cClass const & RetClass() const;
        virtual bool IsA(Fun_Runtime::cClass const &) const;
    private:
        CD2_LAYOUT_CHECKS(cChainGun,
            CD2_SIZE(cChainGun, 0xAC0))

    public:
        // CD2 table 0x82122960 differs from cCWFirearm at these inherited slots.
        virtual float RetAttackDuration() const; // slot 383: 0x82616E10

    private:
        // CD2 table 0x82122960 differs from cCWFirearm at these inherited slots.
        virtual float RetBulletDamageOverride(); // slot 410: 0x82616E60
    };
}

#endif // EQUIP_CCHAINGUN_H
