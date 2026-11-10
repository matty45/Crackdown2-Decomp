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
        // CD2: cGrenade's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8229DF90
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8261D5C0
        virtual void Slot24(); // 24: 0x8261F1F8
        virtual void vf76(); // 76: 0x8261F060
        virtual void vf140(); // 140: 0x8261C148
        virtual void vf158(); // 158: 0x82277CE8
        virtual void vf166(); // 166: 0x827E56A8
        virtual void vf258(); // 258: 0x8261F348
        virtual void vf259(); // 259: 0x8261F360
        virtual void vf260(); // 260: 0x8261F378
        virtual void vf261(); // 261: 0x8261F390
        virtual void vf262(); // 262: 0x8261F3E8
        virtual void vf275(); // 275: 0x8261F528
        virtual void vf284(); // 284: 0x8261F1A0
        virtual void vf300(); // 300: 0x8261F588
        virtual void SetStatus(Equip::cEquipment::EQUIP_STATUS); // 316: 0x8261EEF8
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x821FE5B8
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x821FEA10
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x82889198
    private:
        CD2_LAYOUT_CHECKS(cGrenade, CD2_SIZE(cGrenade, 0x9C0))
    };
}
#endif
