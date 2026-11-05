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
        // CD2 0x8262FCA0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8262FCB0: restores this class's vtables, then calls the base destructor (out of line: derived destructors call it).
        virtual ~cCWHeavyWeapon();
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cCWHeavyWeaponPrototype : public cCWWeapon::cCWWeaponPrototype {};

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
    private:
        unsigned char m_unmodelledA10[0xA20 - 0xA10];
        CD2_LAYOUT_CHECKS(cCWHeavyWeapon, CD2_SIZE(cCWHeavyWeapon, 0xA20))
    };
}
#endif
