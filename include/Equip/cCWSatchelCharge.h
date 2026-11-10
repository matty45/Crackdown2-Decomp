// STAND-IN: RuffKing cCWSatchelCharge derives from cExplosiveGrenade.
// CD2 constructor 0x8261A2E0 calls 0x8261D2E0 before initializing its own
// fields. Descriptor 0x8261A248 gives complete size 0xAE0; those fields remain opaque.
#ifndef EQUIP_CCWSATCHELCHARGE_H
#define EQUIP_CCWSATCHELCHARGE_H
#include "Equip/cExplosiveGrenade.h"
namespace Equip
{
    class cCWSatchelCharge : public cExplosiveGrenade
    {
    public:
        // CD2 0x8261A220: placement factory.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8261A568: restores this class's vtables, then calls the base destructor (out of line: cProxMine's calls it).
        virtual ~cCWSatchelCharge();
        // Name and base from RuffKing. CD2: cCWSatchelCharge::MakeNew (0x8261A1B8) allocates 0x430 and calls this
        // constructor (0x8261CA88), which calls cExplosiveGrenadePrototype's (0x821FE7C8).
        class cCWSatchelChargePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype
        {
        public:
            cCWSatchelChargePrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled390[0x430 - 0x390];

            CD2_LAYOUT_CHECKS(cCWSatchelChargePrototype,
                CD2_SIZE(cCWSatchelChargePrototype, 0x430))
        };

        // CD2 0x8261A210: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCWSatchelChargeClass;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    private:
        unsigned char m_unmodelled9D0[0xAE0 - 0x9D0];
        // CD2: cCWSatchelCharge's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8261B0E8
        virtual bool EnterPhysicalState(); // 7: 0x8261C198
        virtual void Slot14(); // 14: 0x8261A610
        virtual void Slot23(); // 23: 0x8261A7A0
        virtual void Slot24(); // 24: 0x8261A8A8
        virtual void UpdateRenderMatrix(); // 26: 0x8261A988
        virtual void Slot27(); // 27: 0x8261C240
        virtual void vf158(); // 158: 0x8261BAB8
        virtual void vf168(); // 168: 0x8261A688
        virtual void SetStatus(Equip::cEquipment::EQUIP_STATUS); // 316: 0x8261AA20
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x82620970
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x826209B0
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x82882258
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x8260BAE8
    private:
        // CD2: cCWSatchelCharge's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual unsigned int RetTotalAmmo() const; // 332: 0x8260BAF8
        virtual bool CanForceNetTransform() const; // 347: 0x8261CA48
        virtual bool CanReleaseNetOwnershipOnAVExit() const; // 348: 0x827E56A8
    private:
        CD2_LAYOUT_CHECKS(cCWSatchelCharge, CD2_SIZE(cCWSatchelCharge, 0xAE0))
    };
}
#endif
