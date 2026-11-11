#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
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
        class cChainGunPrototype : public cCWFirearm::cCWFirearmPrototype
        {
        public:
            cChainGunPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled6E0[0x780 - 0x6E0];

            CD2_LAYOUT_CHECKS(cChainGunPrototype,
                CD2_SIZE(cChainGunPrototype, 0x780))
        };

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
        float m_fBarrelSpeed;                      // 0xAB0 (RuffKing's names)
        float m_fExtendTrans;                      // 0xAB4
        unsigned char m_unmodelledAB8[0xAC0 - 0xAB8];

        // CD2: cChainGun's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot23(); // 23: 0x82616828
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x82617C88
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x82617C90
    private:
        CD2_LAYOUT_CHECKS(cChainGun,
            CD2_SIZE(cChainGun, 0xAC0))

    public:
        // CD2 table 0x82122960 differs from cCWFirearm at these inherited slots.
        virtual void vf383(); // slot 383: 0x82616E10

    public:
        // CD2 table 0x82122960 differs from cCWFirearm at these inherited slots.
        virtual void vf410(); // slot 410: 0x82616E60
    };
}

#endif // EQUIP_CCHAINGUN_H
