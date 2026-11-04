// STAND-IN: RuffKing names cWeapon as the base; CD2 constructor 0x8261E238
// confirms that constructor chain. Descriptor 0x8225D5D8 gives complete size 0x9C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CGRENADE_H
#define EQUIP_CGRENADE_H
#include "Equip/cWeapon.h"
namespace Equip
{
    class cGrenade : public cWeapon
    {
    public:
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cGrenadePrototype : public cWeapon::cWeaponPrototype {};

        // CD2 factory 0x8261DFA8 forwards only this, without a prototype argument.
        cGrenade();
        // CD2 0x8261DF98: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGrenadeClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
    private:
        unsigned char m_unmodelled8C0[0x9C0 - 0x8C0];
        CD2_LAYOUT_CHECKS(cGrenade, CD2_SIZE(cGrenade, 0x9C0))
    };
}
#endif
