// STAND-IN: RuffKing names cGrenade as the base; CD2 constructor 0x8260B288 (inlined factory)
// confirms that constructor chain. Descriptor 0x822F33C8 gives complete size 0x9C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CCLOAKINGDEVICE_H
#define EQUIP_CCLOAKINGDEVICE_H
#include "Equip/cGrenade.h"
namespace Equip
{
    class cCloakingDevice : public cGrenade
    {
    public:
        // Inline: CD2's placement factory (0x8260B288) calls cGrenade's (0x8261E238) constructor, then stores this class's vptrs.
        __forceinline cCloakingDevice() {}
        // CD2 0x8260B350: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260BA80).
        // CD2 factory allocates 0x380; attributes independently confirm the two reference-named fields.
        class cCloakingDevicePrototype : public cGrenade::cGrenadePrototype
        {
        public:
            // CD2 inlines construction into MakeNew; the grenade prototype remains an out-of-line call.
            __forceinline cCloakingDevicePrototype(const RWS::CAttributePacket &packet)
                : cGrenadePrototype(packet), m_fArmourDrainAmount(40.0f), m_bItemUsesAmmo(false)
            {
                m_EquipmentType = eEquipT_Secondary;
            }
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            bool CanItemUseAmmo() const { return m_bItemUsesAmmo; }
        protected:
            float m_fArmourDrainAmount;
            bool m_bItemUsesAmmo;
            CD2_LAYOUT_CHECKS(cCloakingDevicePrototype,
                CD2_SIZE(cCloakingDevicePrototype, 0x380)
                CD2_OFFSET(cCloakingDevicePrototype, m_fArmourDrainAmount, 0x370)
                CD2_OFFSET(cCloakingDevicePrototype, m_bItemUsesAmmo, 0x374))
        };

        // CD2 0x8260B278: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCloakingDeviceClass;
        // CD2 0x8260B1E8; its class-factory registrar (0x82FCC720) names it.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8260B188: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x8260B4B0.
        virtual ~cCloakingDevice();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2: cCloakingDevice's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8260B460
        virtual bool ShouldBeForceStored(); // 317: 0x827E56A8
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8261F5F0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82396118
    public:
        CD2_LAYOUT_CHECKS(cCloakingDevice, CD2_SIZE(cCloakingDevice, 0x9C0))

    public:
        // CD2 table 0x82014720 differs from cGrenade at these inherited slots.
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // slot 18: 0x8260B430
        virtual bool BeginAttack(); // slot 378: 0x8260B8C8
        virtual void ProcessAttack(); // slot 379: 0x8260B788
        virtual void EndAttack(); // slot 380: 0x8260B978
        virtual bool CanAttack(); // slot 381: 0x8260B360
        virtual bool CanItemUseAmmo() const; // Slot 409: 0x8260B3D0.
        virtual void vf410(); // slot 410: 0x8260B558
    protected:
        void DeCloak(); // RuffKing name; CD2 0x8260B5A0 clears the owner's cloak state.
        const cCloakingDevicePrototype *RetCloakPrototype() const
        {
            return static_cast<const cCloakingDevicePrototype *>(m_pPrototype);
        }
    };
}
#endif
