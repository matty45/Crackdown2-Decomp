// CHARACTER::cCwTransCharacter (Crackdown 2 only; Burn calls it cPlayerCharacter): STAND-IN, sized to CD2. Evidence:
// its StaticCreateClass builds cClass(0x6A1, "cCwTransCharacter", 0x2E00); its constructor 0x82231358 (its
// SpawnFromPrototype tail-calls it) calls cCharacter's constructor 0x82543408. CD2's cFrontEndAgent also derives from
// it.
// Burn's cPlayerCharacter gives the skill-set, invulnerability, death-limbo, friendly-kill and last-vehicle member
// names. CD2 has m_SkillSet at +0x2CC4 (its transform flag at +0x2D20), a 16-bit power-up mask at +0x2D64,
// death-limbo/friendly-kill flags at +0x2DA4/+0x2DA5 and last vehicle ID at +0x2DD0. Byte +0x2DA6 remains unnamed.
// cCharacter's recovered primary slots give the prefix for these overrides; each slot is checked against CD2.
#ifndef CHARACTER_CCWTRANSCHARACTER_H
#define CHARACTER_CCWTRANSCHARACTER_H

#include "CHARACTER/cCharacter.h"
#include "gom/object_prototype.h"
#include "RPG/cSkillSet.h"

namespace CHARACTER
{
    class cCwTransCharacter : public cCharacter
    {
    private:
        unsigned int m_nInvulnerableEnd;
        RPG::cSkillSet m_SkillSet;
        unsigned char m_unmodelled2D28[0x2D64 - 0x2D28];
        unsigned short m_nPowerUpStatus;
        unsigned char m_pad2D66[0x2DA4 - 0x2D66];
        bool m_bInDeathLimbo;
        bool m_bKilledByFriendly;
        unsigned char m_byte2DA6;
        unsigned char m_pad2DA7[0x2DD0 - 0x2DA7];
        unsigned int m_nLastVehicleHitID;
        unsigned char m_pad2DD4[0x2E00 - 0x2DD4];

    public:
        static const Fun_Runtime::cClass *ms_pcCwTransCharacterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // STAND-IN, name follows this class's prototype factory. CD2 0x825380E8 allocates 0x460 bytes;
        // constructor 0x82312E00 calls cCharacterPrototype's constructor (0x8254D4C8) first.
        class cCwTransCharacterPrototype : public cCharacter::cCharacterPrototype
        {
        private:
            unsigned char m_unmodelled330[0x460 - 0x330];
        public:
            cCwTransCharacterPrototype(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cCwTransCharacterPrototype,
                CD2_SIZE(cCwTransCharacterPrototype, 0x460))
        };

        // CD2 0x82538150 forwards the prototype to constructor 0x82231358.
        cCwTransCharacter(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 primary slot 391; the embedded skill set owns the transformation flag.
        virtual bool IsTransformationRequired() const;
        virtual unsigned char RetAthleticLevel() const;
        virtual unsigned char RetExplosivesLevel() const;
        virtual unsigned char RetStrengthLevel() const;
        virtual unsigned char RetFirearmsLevel() const;
        virtual bool IsSkillAndBonusMaxed(unsigned int skill) const;
        virtual bool IsSkillMaxed(unsigned int skill) const;
        virtual bool IsPowerUpActive(ePowerUp powerUp);
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual bool IsInDeathLimbo() const;
        virtual void SetKilledByFriendly(bool friendly);
        virtual unsigned int RetLastVehicleHitID() const;

        CD2_LAYOUT_CHECKS(cCwTransCharacter,
            CD2_SIZE(cCwTransCharacter, 0x2E00)
            CD2_OFFSET(cCwTransCharacter, m_nInvulnerableEnd, 0x2CC0)
            CD2_OFFSET(cCwTransCharacter, m_SkillSet, 0x2CC4)
            CD2_OFFSET(cCwTransCharacter, m_nPowerUpStatus, 0x2D64)
            CD2_OFFSET(cCwTransCharacter, m_bInDeathLimbo, 0x2DA4)
            CD2_OFFSET(cCwTransCharacter, m_bKilledByFriendly, 0x2DA5)
            CD2_OFFSET(cCwTransCharacter, m_byte2DA6, 0x2DA6)
            CD2_OFFSET(cCwTransCharacter, m_nLastVehicleHitID, 0x2DD0))
    };
}

#endif // CHARACTER_CCWTRANSCHARACTER_H
