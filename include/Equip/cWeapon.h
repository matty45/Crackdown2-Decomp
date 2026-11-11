// STAND-IN: RuffKing names cEquipment as the base; CD2 constructor 0x82609AA8
// confirms that constructor chain. Descriptor 0x822E5B60 gives complete size 0x8C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CWEAPON_H
#define EQUIP_CWEAPON_H
#include "Equip/cEquipment.h"
namespace Equip
{
    class cWeapon : public cEquipment
    {
    public:
        // CD2 weapon interface extends the 363-slot equipment interface; reference virtual order gives 43 own slots. Names/signatures of these slots remain unrecovered.
        virtual void vf363(); // primary slot 363
        virtual void vf364(); // primary slot 364
        virtual void vf365(); // primary slot 365
        virtual void vf366(); // primary slot 366
        virtual void vf367(); // primary slot 367
        virtual void vf368(); // primary slot 368
        virtual void vf369(); // primary slot 369
        virtual void vf370(); // primary slot 370
        virtual void vf371(); // primary slot 371
        virtual void vf372(); // primary slot 372
        virtual void vf373(); // primary slot 373
        virtual void vf374(); // primary slot 374
        virtual void vf375(); // primary slot 375
        virtual void vf376(); // primary slot 376
        virtual void vf377(); // primary slot 377
        virtual void vf378(); // primary slot 378
        virtual void vf379(); // primary slot 379
        virtual void vf380(); // primary slot 380
        virtual void vf381(); // primary slot 381
        virtual void vf382(); // primary slot 382
        virtual void vf383(); // primary slot 383
        virtual void vf384(); // primary slot 384
        virtual void vf385(); // primary slot 385
        virtual void vf386(); // primary slot 386
        virtual void vf387(); // primary slot 387
        virtual void vf388(); // primary slot 388
        virtual void vf389(); // primary slot 389
        virtual void vf390(); // primary slot 390
        virtual void vf391(); // primary slot 391
        virtual void vf392(); // primary slot 392
        virtual void vf393(); // primary slot 393
        virtual void vf394(); // primary slot 394
        virtual void vf395(); // primary slot 395
        virtual void vf396(); // primary slot 396
        virtual void vf397(); // primary slot 397
        virtual void vf398(); // primary slot 398
        virtual void vf399(); // primary slot 399
        virtual void vf400(); // primary slot 400
        virtual void vf401(); // primary slot 401
        virtual void vf402(); // primary slot 402
        virtual void vf403(); // primary slot 403
        virtual void vf404(); // primary slot 404
        virtual void vf405(); // primary slot 405

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        // Name and base from RuffKing. CD2's constructor (0x8260A370) calls cEquipmentPrototype's and initializes
        // 0x29C..0x34B; cGrenadePrototype's constructor (0x8261F758) starts its own fields at 0x350.
        class cWeaponPrototype : public cEquipment::cEquipmentPrototype
        {
        public:
            cWeaponPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled2F0[0x350 - 0x2F0];

            CD2_LAYOUT_CHECKS(cWeaponPrototype,
                CD2_SIZE(cWeaponPrototype, 0x350))
        };

        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcWeaponClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
    private:
        unsigned char m_unmodelled870[0x8C0 - 0x870];
        // CD2: cWeapon's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void vf140(); // 140: 0x8234A320
        virtual void vf274(); // 274: 0x82335618
        virtual void vf275(); // 275: 0x82609F30
        virtual void vf276(); // 276: 0x82609FA8
    private:
        CD2_LAYOUT_CHECKS(cWeapon, CD2_SIZE(cWeapon, 0x8C0))

    public:
        // CD2 table 0x8211F3C8 differs from cEquipment at these inherited slots.
        virtual void Slot13(); // slot 13: 0x823A7408
        virtual void Slot23(); // slot 23: 0x82609BA8
        virtual void vf288(); // slot 288: 0x827E56A8
        virtual void SetStatus(EQUIP_STATUS); // slot 316: 0x82609BF0
        virtual bool Activate(); // slot 318: 0x82609C58
        virtual unsigned int RetWeaponPriority() const; // slot 320: 0x82609F00
        virtual bool HasMaxAmmo() const; // slot 333: 0x82607A80
        virtual bool IsMarkedForDeletion(); // slot 334: 0x82378A28
    };
}
#endif
