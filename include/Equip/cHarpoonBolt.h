#include "rws/attributes.h"
// Equip::cHarpoonBolt (Crackdown 2): STAND-IN for the class name only. Base Equip::cWeaponProjectile, as in RuffKing's
// header; RetClassName (0x826271D8) is slot 11 of the vtable at 0x82010B60, as cNonGameBase's RetClassName.
#ifndef EQUIP_CHARPOONBOLT_H
#define EQUIP_CHARPOONBOLT_H

#include "Equip/cWeaponProjectile.h"
#include "fun_runtime/class.h"
#include "fun_runtime/safedeletablepointer.h"
#include "gom/game_base.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace Equip
{
    class cHarpoonBolt : public Equip::cWeaponProjectile
    {
    public:
        // Name and base from RuffKing. CD2's MakeNew (0x82627168) allocates 0x2F0, calls cEquipmentPrototype's
        // constructor (0x826071F8) and stores this class's vptrs: both derived constructors are inline and add no
        // fields.
        class cHarpoonBoltPrototype : public cWeaponProjectile::cWeaponProjectilePrototype
        {
        public:
            __forceinline cHarpoonBoltPrototype(const RWS::CAttributePacket &packet)
                : cWeaponProjectile::cWeaponProjectilePrototype(packet) {}

            // CD2: cHarpoonBoltPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82629020
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82629028
        public:
            CD2_LAYOUT_CHECKS(cHarpoonBoltPrototype,
                CD2_SIZE(cHarpoonBoltPrototype, 0x2F0))
        };

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cHarpoonBolt();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcHarpoonBoltClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x826270F8 / 0x82627108: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x82627778 (its deleting destructor 0x826274D0 calls it): destroys the two safe pointers, then
        // cWeaponProjectile's.
        virtual ~cHarpoonBolt();

        // CD2 table 0x82010B60 (stored by the destructor) differs from cWeaponProjectile's 0x820105B0 at these slots;
        // names and signatures are the bases'. RuffKing's harpoon overrides SetDeletingReason/GetDeletingReason too.
        virtual Fun_Runtime::RetVal Term();                         // 6: 0x826275C8
        virtual bool EnterPhysicalState();                          // 7: 0x827E56A8
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *);    // 18: 0x82627520
        virtual void TickUpdate(float fDeltaTime);                  // 23: 0x82627880
        virtual void Slot29();                                      // 29: 0x827E56A8
        virtual void Slot64();                                      // 63: 0x82627878
        virtual void SetDeletingReason(char);                       // 309: 0x82627200
        virtual char GetDeletingReason();                           // 310: 0x82627208
        virtual Fun_Runtime::cString GetNetDebugString();           // 346: 0x827E56A8
        // Replication table 0x82127040 differs from cWeaponProjectile's 0x8211FC50 here.
        virtual void CalculateRelevancy(int);                       // cReplicatedClass 2: 0x82580578
        virtual void CalculateLOD(int);                             // cReplicatedClass 3: 0x82628F18
        virtual void ReplicateInitialFields();                      // cReplicatedClass 8: 0x82628950
        virtual void ReplicateFields();                             // cReplicatedClass 9: 0x82628AD8
        virtual void ReplicateHeaderData();                         // cReplicatedClass 10: 0x82628848
        virtual void SkipDefaultReplicatedFields();                 // cReplicatedClass 11: 0x82580578
        virtual unsigned int GetNumObjectIDBits() const;            // cReplicatedClass 16: 0x82882258
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const; // cReplicatedClass 22: 0x825ECFA8
        virtual unsigned int GetMaxReplicatedFields() const;        // cReplicatedClass 23: 0x8288B098

    private:
        // RuffKing's members, 0x20 earlier in CD2 (descriptor size 0x910 = RuffKing's 0x930 - 0x20). CD2's destructor
        // installs one typed safe-pointer table (0x82155680) for both pointers from one register, so they share a
        // pointee type; RuffKing's first one, cGameBase, is used for both.
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pAttatchedObject;      // 0x870
        unsigned char m_unmodelled880[0x8F8 - 0x880];
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pHarpoonedCharacter;   // 0x8F8
        unsigned char m_unmodelled908[0x910 - 0x908];

        CD2_LAYOUT_CHECKS(cHarpoonBolt,
            CD2_SIZE(cHarpoonBolt, 0x910)
            CD2_OFFSET(cHarpoonBolt, m_pAttatchedObject, 0x870)
            CD2_OFFSET(cHarpoonBolt, m_pHarpoonedCharacter, 0x8F8))
    };
}

#endif // EQUIP_CHARPOONBOLT_H
