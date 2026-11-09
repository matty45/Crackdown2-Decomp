// CHARACTER::cCharacterInterface (Crackdown 2): STAND-IN, sized to CD2; only what matched code needs so far. Evidence:
//   - Size 0xC0: cClass(0x5ED, "cCharacterInterface", 0xC0). Base cNonGameBase: its constructor 0x8254EC78 calls
//     cNonGameBase's.
//   - m_pCharacter (0x7C) is a Fun_Runtime::cSafeDeletablePointer<cCharacter> (RuffKing's type): its constructor installs the pointer-list vptr,
//     its object pointer is at 0x88, and its destructor unlinks it from the pointed-to object's list.
//   - RetCharacter is inline (no out-of-line copy in RuffKing or CD2): PLAYER::cPlayer::SetAITargeting reads 0x88,
//     null-tests it, subtracts 0x1C (cSafeDeletable's offset in cNonGameBase) and null-tests again.
//   - The sound-event times (RuffKing names; RuffKing has them at 0xD0..0xD8): cAiPlayer's primary vtable slots 112 and
//     113 (0x823EB518, 0x823EB570) do what RuffKing's cAiPlayer::ShouldTriggerFootStepEvent (LOD level at most 1, 10 s)
//     and ShouldTriggerBulletSoundEvent (3 s) do, on 0xA0 and 0xA8; slot 111 (0x8237B148, its own interval) updates
//     0xA4. RuffKing declares the three virtuals as Vocal, FootStep, BulletSound and the fields as FootStep, Vocal,
//     BulletSound, which fits.
//   - cAiPlayer::ShouldTriggerFootStepEvent reads the character's level directly; this interface's script wrapper
//     0x8254E8C8 is registered as "RetLODLevel".
//   - Script setters 0x8254EA80 and 0x8254EA88 name the flags at 0xAE and 0xAF:
//     SetCanShareVehicleWithPlayer and SetCanBePickedUpWhenAlive, respectively.
// g_cCharacterInterface is named after the type it is registered as ("cCharacterInterface", through 0x82772828; see
// AI/cAiPlayer.h). RetScriptTypeRegistration (0x8254E8A8) returns it: slot 1 of the cScriptHost table 0x82113DF4, which
// the constructor installs (0x8254ECC0). 0x8254E8B8 (returns "eLODLevel") is slot 1 of an enum registrar's table.
#ifndef CHARACTER_CCHARACTERINTERFACE_H
#define CHARACTER_CCHARACTERINTERFACE_H

#include "gom/non_game_base.h"
#include "gom/object_prototype.h"
#include "fun_runtime/safedeletable.h"
#include "fun_runtime/safedeletablepointer.h"
#include "CHARACTER/cCharacter.h"
#include "cd2/layout.h"
namespace Prop { class cTurretBase; }

namespace CHARACTER
{
    class cCharacterInterface : public cNonGameBase
    {
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacter> m_pCharacter; // 0x7C
    private:
        unsigned char m_pad8C[0x90 - 0x8C];
        Fun_Runtime::Vec3 m_vecCentre;                    // 0x90
    protected:
        float m_fLastFootStepSoundTime;                     // 0xA0
        float m_fLastVocalSoundTime;                        // 0xA4
        float m_fLastBulletSoundTime;                       // 0xA8
    private:
        unsigned char m_padAC;
        bool m_bInitialState;                               // 0xAD: name ours; initialized false by the constructor
    protected:
        bool m_bCanShareVehicleWithPlayer;
        bool m_bCanBePickedUpWhenAlive;
        bool m_bAlive;                                      // 0xB0 (RuffKing name)
    private:
        unsigned char m_padB1[0xC0 - 0xB1];

    public:
        static const Fun_Runtime::cClass *ms_pcCharacterInterfaceClass;

        // RuffKing: cCharacterInterfacePrototype : cNonGameBase::cNonGameBasePrototype (: GOM::cObjectPrototype), 0x70
        // bytes. CD2's MakeNew (0x8254E810) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118)
        // with the packet and installs the vtables 0x82113E2C (at 0) and 0x821327A4 (at 0x18, shared by every
        // prototype): no fields of its own, and cNonGameBasePrototype adds none either, so it is not modelled.
        class cCharacterInterfacePrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this into MakeNew, which this compiler does only when forced
            // (docs/matching-notes.md, "Inlining").
            __forceinline cCharacterInterfacePrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}
        };

        // CD2 0x8254EC78 takes no prototype argument; 0x8254E890 is its placement factory.
        cCharacterInterface();
        virtual ~cCharacterInterface();
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2 0x8254E8A8: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        void SetCanShareVehicleWithPlayer(bool enabled);
        void SetCanBePickedUpWhenAlive(bool enabled);
        // Script getter 0x825430D8 is folded into cCharacter.cpp, and reads this interface's flag.
        bool CanBePickedUpWhenAlive() const;
        bool RetIsOnFire() const;
        cGameBase *RetVehicleTarget();
        Equip::cEquipment *RetEquipmentOfType(unsigned int type);
        Equip::cEquipment *RetRealCurrentPrimaryEquipment();
        bool IsEquipmentTypeInInventory(unsigned int type);
        // CD2 0x823E7778: shared character-interface override, outside the current source split.
        virtual bool IsAlive() const { return m_bAlive; }

        // CD2 table 0x82113C10 has 115 primary slots. Names are given only where CD2's call/data flow
        // and the reference declaration order agree; other own slots retain their numeric placeholders.
        virtual void vf68();
        virtual void vf69();
        virtual void vf70();
        virtual void vf71();
        virtual void vf72();
        virtual void vf73();
        virtual void vf74();
        virtual void vf75();
        virtual void vf76();
        virtual void vf77();
        virtual void vf78();
        virtual void vf79();
        virtual void vf80();
        virtual void vf81();
        virtual void vf82();
        virtual void vf83();
        virtual void vf84();
        virtual void vf85();
        virtual void vf86();
        virtual void vf87();
        virtual void vf88();
        virtual void vf89();
        virtual void vf90();
        virtual void vf91();
        virtual void vf92();
        virtual void vf93();
        virtual void vf94();
        virtual void vf95();
        virtual void vf96();
        virtual void vf97();
        virtual void vf98();
        virtual void vf99();
        virtual bool ForceIntoVehicle(Vehicle::cVehicle *, unsigned int);
        virtual bool ForceOutOfVehicle();
        virtual bool ForceRappel();
        virtual bool ForceOntoTurret(Prop::cTurretBase *);
        virtual bool ForceDead();
        virtual void vf105();
        virtual void vf106();
        virtual void vf107();
        virtual void vf108();
        virtual void vf109();
        virtual void vf110();
        virtual bool ShouldTriggerVocalEvent();
        virtual bool ShouldTriggerFootStepEvent();
        virtual bool ShouldTriggerBulletSoundEvent();
        virtual void vf114();

        cCharacter *RetCharacter() const
        {
            return m_pCharacter.m_pPtr ? static_cast<cCharacter *>(m_pCharacter.m_pPtr) : 0;
        }

        unsigned char RetLODLevel() const;
        float RetHealthFraction();

        CD2_LAYOUT_CHECKS(cCharacterInterface,
            CD2_SIZE(cCharacterInterface, 0xC0)
            CD2_OFFSET(cCharacterInterface, m_pCharacter, 0x7C)
            CD2_OFFSET(cCharacterInterface, m_vecCentre, 0x90)
            CD2_OFFSET(cCharacterInterface, m_fLastFootStepSoundTime, 0xA0)
            CD2_OFFSET(cCharacterInterface, m_fLastVocalSoundTime, 0xA4)
            CD2_OFFSET(cCharacterInterface, m_fLastBulletSoundTime, 0xA8)
            CD2_OFFSET(cCharacterInterface, m_bCanShareVehicleWithPlayer, 0xAE)
            CD2_OFFSET(cCharacterInterface, m_bCanBePickedUpWhenAlive, 0xAF)
            CD2_OFFSET(cCharacterInterface, m_bAlive, 0xB0))
    };
}

#endif // CHARACTER_CCHARACTERINTERFACE_H
