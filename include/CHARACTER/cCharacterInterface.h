// CHARACTER::cCharacterInterface (Crackdown 2): STAND-IN, sized to CD2; only what matched code needs so far. Evidence:
//   - Size 0xC0: cClass(0x5ED, "cCharacterInterface", 0xC0). Base cNonGameBase: its constructor 0x8254EC78 calls
//     cNonGameBase's.
//   - The constructor stores the vptr of Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pCharacter
//     (RuffKing name and type) at 0x7C and nulls that pointer's object pointer at 0x88 (RuffKing's
//     cSafeDeletablePointerBase:
//     cLinkedListItem, then m_pPtr at +0xC). The shared Fun_Runtime::cSafeDeletablePointerBase keeps that word private,
//     so the safe pointer is laid out flat here until it exposes it.
//   - RetCharacter is inline (no out-of-line copy in RuffKing or CD2): PLAYER::cPlayer::SetAITargeting reads 0x88,
//     null-tests it, subtracts 0x1C (cSafeDeletable's offset in cNonGameBase) and null-tests again.
//   - The sound-event times (RuffKing names; RuffKing has them at 0xD0..0xD8): cAiPlayer's primary vtable slots 112 and
//     113 (0x823EB518, 0x823EB570) do what RuffKing's cAiPlayer::ShouldTriggerFootStepEvent (LOD level at most 1, 10 s)
//     and ShouldTriggerBulletSoundEvent (3 s) do, on 0xA0 and 0xA8; slot 111 (0x8237B148, its own interval) updates
//     0xA4. RuffKing declares the three virtuals as Vocal, FootStep, BulletSound and the fields as FootStep, Vocal,
//     BulletSound, which fits.
//   - RetLODLevel is inline in CD2 (cAiPlayer::ShouldTriggerFootStepEvent reads the character's level directly); its
//     out-of-line copy 0x8254E8C8 is the script method "RetLODLevel".
//   - Script setters 0x8254EA80 and 0x8254EA88 name the flags at 0xAE and 0xAF:
//     SetCanShareVehicleWithPlayer and SetCanBePickedUpWhenAlive, respectively.
#ifndef CHARACTER_CCHARACTERINTERFACE_H
#define CHARACTER_CCHARACTERINTERFACE_H

#include "gom/non_game_base.h"
#include "gom/object_prototype.h"
#include "fun_runtime/safedeletable.h"
#include "CHARACTER/cCharacter.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cCharacterInterface : public cNonGameBase
    {
    protected:
        unsigned char m_pCharacterLink[0xC];                // 0x7C: m_pCharacter's vptr and list links
        Fun_Runtime::cSafeDeletable *m_pCharacterPtr;       // 0x88: m_pCharacter's object pointer
    private:
        unsigned char m_pad8C[0xA0 - 0x8C];
    protected:
        float m_fLastFootStepSoundTime;                     // 0xA0
        float m_fLastVocalSoundTime;                        // 0xA4
        float m_fLastBulletSoundTime;                       // 0xA8
    private:
        unsigned char m_padAC[0xAE - 0xAC];
        bool m_bCanShareVehicleWithPlayer;
        bool m_bCanBePickedUpWhenAlive;
        unsigned char m_padB0[0xC0 - 0xB0];

    public:
        // CD2 0x8254EC78 takes no prototype argument; 0x8254E890 is its placement factory.
        cCharacterInterface();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        void SetCanShareVehicleWithPlayer(bool enabled);
        void SetCanBePickedUpWhenAlive(bool enabled);
        // Script getter 0x825430D8 is folded into cCharacter.cpp, and reads this interface's flag.
        bool CanBePickedUpWhenAlive() const;
        bool RetIsOnFire() const;

        cCharacter *RetCharacter() const
        {
            return m_pCharacterPtr ? static_cast<cCharacter *>(m_pCharacterPtr) : 0;
        }

        unsigned char RetLODLevel() const { return RetCharacter()->RetLODLevel(); }

        CD2_LAYOUT_CHECKS(cCharacterInterface,
            CD2_SIZE(cCharacterInterface, 0xC0)
            CD2_OFFSET(cCharacterInterface, m_pCharacterPtr, 0x88)
            CD2_OFFSET(cCharacterInterface, m_fLastFootStepSoundTime, 0xA0)
            CD2_OFFSET(cCharacterInterface, m_fLastVocalSoundTime, 0xA4)
            CD2_OFFSET(cCharacterInterface, m_fLastBulletSoundTime, 0xA8)
            CD2_OFFSET(cCharacterInterface, m_bCanShareVehicleWithPlayer, 0xAE)
            CD2_OFFSET(cCharacterInterface, m_bCanBePickedUpWhenAlive, 0xAF))
    };
}

#endif // CHARACTER_CCHARACTERINTERFACE_H
