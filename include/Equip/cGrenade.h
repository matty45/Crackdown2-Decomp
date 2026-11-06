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
        // CD2 0x8261DFC0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8261E460 (out of line: cExplosiveGrenade's and cCloakingDevice's destructors call it).
        virtual ~cGrenade();
        // Name and base from RuffKing. CD2: cGrenade::MakeNew (0x8261DF40) allocates 0x370 and calls this constructor
        // (0x8261F758), which calls cWeaponPrototype's (0x8260A370).
        class cGrenadePrototype : public cWeapon::cWeaponPrototype
        {
        public:
            cGrenadePrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled350[0x370 - 0x350];

            CD2_LAYOUT_CHECKS(cGrenadePrototype,
                CD2_SIZE(cGrenadePrototype, 0x370))
        };

        // CD2 factory 0x8261DFA8 forwards only this, without a prototype argument.
        cGrenade();
        // CD2 0x8261DF98: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGrenadeClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    private:
        unsigned char m_unmodelled8C0[0x9C0 - 0x8C0];
        CD2_LAYOUT_CHECKS(cGrenade, CD2_SIZE(cGrenade, 0x9C0))
    };
}
#endif
