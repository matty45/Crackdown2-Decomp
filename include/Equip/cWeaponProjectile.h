#include "gom/object_prototype.h"
#include "fun_runtime/class.h"
// Base cEquipment: CD2's constructor 0x82609610 calls cEquipment's (0x82604AF8) and the destructor 0x826096C0 calls
// cEquipment's (0x82604CA8); both only restore this class's vtables. Derived storage is not modelled.
#ifndef Equip_cWeaponProjectile_H
#define Equip_cWeaponProjectile_H

#include "Equip/cEquipment.h"

#include "rws/attributes.h"

namespace Equip
{
    class cWeaponProjectile : public cEquipment
    {
    public:
        static const Fun_Runtime::cClass *ms_pcWeaponProjectileClass;
        // Name and base from RuffKing. CD2's MakeNew (0x82609578) allocates 0x2F0, calls cEquipmentPrototype's
        // constructor (0x826071F8) and stores this class's vptrs: the constructor is inline and adds no fields.
        class cWeaponProjectilePrototype : public cEquipment::cEquipmentPrototype
        {
        public:
            __forceinline cWeaponProjectilePrototype(const RWS::CAttributePacket &packet)
                : cEquipment::cEquipmentPrototype(packet) {}
            // Inline: CD2's deleting destructor (0x82609768) restores this class's vptrs, then calls the base's.
            virtual ~cWeaponProjectilePrototype() {}

            // CD2: cWeaponProjectilePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            // Reconstruction update: these slots are inherited unchanged from
            // cEquipmentPrototype. Its missing HandleAttributes declaration caused
            // the former per-projectile attribution; no overrides are needed here.
            // 1: 0x826073B8
            // 22: 0x827E56A8
        public:
            CD2_LAYOUT_CHECKS(cWeaponProjectilePrototype,
                CD2_SIZE(cWeaponProjectilePrototype, 0x2F0))
        };

        // CD2 factory 0x826095F8 forwards only this, without a prototype argument.
        cWeaponProjectile();
        // CD2 0x826096C0.
        virtual ~cWeaponProjectile();
        // CD2 spawning initializer 0x82FCBFB8 names placement factory 0x826095f8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8260A7A0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // Slot 363, the class's one new virtual (RuffKing: PickUpRequested(), beside cEquipment's with an owner).
        virtual bool PickUpRequested();
        // CD2: cWeaponProjectile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        // virtual Fun_Runtime::RetVal Term(); // 6: 0x82604D68
        // Reconstruction update: slot 6 inherits cEquipment::Term unchanged.
        virtual void Slot13(); // 13: 0x82604F48
        // virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8228C898
        // Reconstruction update: slot 18 inherits cDynamicBody::Init unchanged.
        virtual void Slot23(); // 23: 0x822D04B8
        virtual void vf258(); // 258: 0x82580578
        virtual void vf259(); // 259: 0x82580578
        virtual void vf260(); // 260: 0x82580578
        virtual void vf261(); // 261: 0x82580578
        virtual void vf262(); // 262: 0x82580578
        virtual void vf288(); // 288: 0x82686390
        virtual void SetStatus(Equip::cEquipment::EQUIP_STATUS); // 316: 0x82605128
        virtual bool Activate(); // 318: 0x827E56A8
        virtual unsigned int RetWeaponPriority() const; // 320: 0x827E56A8
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8260AA68
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8260AA98
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x82606198
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x822F3468
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288E110
        // CD2: cWeaponProjectile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HasMaxAmmo() const; // 333: 0x827E56A8
        virtual bool IsMarkedForDeletion(); // 334: 0x827E56A8
        virtual Fun_Runtime::State * RetSTATE_Idle() const; // 357: 0x82604838
        virtual Fun_Runtime::State * RetSTATE_Idle(); // 358: 0x82604838
        virtual Fun_Runtime::State * RetSTATE_Active() const; // 359: 0x82604888
        virtual Fun_Runtime::State * RetSTATE_Active(); // 360: 0x82604888
    };
}

#endif
