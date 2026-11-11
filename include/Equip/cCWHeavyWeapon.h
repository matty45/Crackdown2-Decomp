// STAND-IN: RuffKing names cCWWeapon as the base; CD2 constructor 0x8262FF78
// confirms that constructor chain. Descriptor 0x8262FE78 gives complete size 0xA20.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CCWHEAVYWEAPON_H
#define EQUIP_CCWHEAVYWEAPON_H
#include "Equip/cCWWeapon.h"
namespace Equip
{
    class cCWHeavyWeapon : public cCWWeapon
    {
    public:
        // CD2 table 0x82013A38 extends the inherited interface at these slots.
        virtual void vf410();

        // CD2 0x8262FCA0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8262FCB0: restores this class's vtables, then calls the base destructor (out of line: derived destructors call it).
        virtual ~cCWHeavyWeapon();
        // Name and base from RuffKing. CD2: cCWHeavyWeapon::MakeNew (0x8262FC20) allocates 0x410 and calls this
        // constructor (0x82630920), which calls cCWWeaponPrototype's (0x82608930).
        class cCWHeavyWeaponPrototype : public cCWWeapon::cCWWeaponPrototype
        {
        public:
            cCWHeavyWeaponPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled3E0[0x410 - 0x3E0];

            CD2_LAYOUT_CHECKS(cCWHeavyWeaponPrototype,
                CD2_SIZE(cCWHeavyWeaponPrototype, 0x410))
        };

        // CD2 factory 0x8262FC88 forwards only this, without a prototype argument.
        cCWHeavyWeapon();
        // CD2 0x8262FC78: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCWHeavyWeaponClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8262FBC0: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    private:
        unsigned char m_unmodelledA10[0xA20 - 0xA10];
        // CD2: cCWHeavyWeapon's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x82608168
        virtual void vf276(); // 276: 0x82630658
        virtual void vf277(); // 277: 0x826306F0
        virtual void vf279(); // 279: 0x82630770
    private:
        CD2_LAYOUT_CHECKS(cCWHeavyWeapon, CD2_SIZE(cCWHeavyWeapon, 0xA20))

    public:
        // CD2 table 0x82013A38 differs from cCWWeapon at these inherited slots.
        virtual void vf378(); // slot 378: 0x82630030
        virtual void vf404(); // slot 404: 0x8262FF10
    };
}
#endif
