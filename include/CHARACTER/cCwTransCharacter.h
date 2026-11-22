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
    // Descriptive identity remains unrecovered: CD2 0x8253BC08 loads this
    // shared float from 0x8373BB20 for primary virtual slot 132.
    extern float g_8373BB20;

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
        // Burn's member follows the ID; CD2 SetLastVehicleHitID writes 0.4f here.
        float m_fLastVehicleHitTimer;
        unsigned char m_pad2DD8[0x2E00 - 0x2DD8];

    public:
        static const Fun_Runtime::cClass *ms_pcCwTransCharacterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // STAND-IN, name follows this class's prototype factory. CD2 0x825380E8 allocates 0x460 bytes;
        // constructor 0x82312E00 calls cCharacterPrototype's constructor (0x8254D4C8) first.
        class cCwTransCharacterPrototype : public cCharacter::cCharacterPrototype
        {
        private:
            // Burn's player prototype names/order. CD2 constructor 0x82312E00
            // fills five four-resource body/head rows at +0x330/+0x380 and clears
            // the five profile/skeleton arrays. Getters 0x825399A0..0x82539A30
            // establish each remaining array's offset and element type.
            RWS::CResource *m_apTransBodyLODs[5][4];
            RWS::CResource *m_apTransHeadLODs[5][4];
            Anim::cAnimationProfile *m_pAnimationProfileArray[5];
            cCharacterProfile *m_pProfileArray[5];
            RPG::cExplosivesSkillProfile *m_pExplosivesArray[5];
            cStrengthSkillProfile *m_pStrengthArray[5];
            unsigned int m_eSkeletonTypeIndex[5];
            float m_fInitMinScales[5];
            float m_fInitMaxScales[5];
        public:
            cCwTransCharacterPrototype(const RWS::CAttributePacket &);
            // CD2 table 0x82005568 slot 5 returns the file's Ret_OK object.
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            // CD2 table 0x82005568 slot 1 (0x82539220); the derived prototypes' tables (0x82162A20, cFrontEndAgent's)
            // keep it.
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            virtual void SetCharacterProfile(unsigned char nLevel, const char *szProfileName);
            virtual void SetExplosivesProfile(unsigned char nLevel, const char *szProfileName);
            virtual void SetStrengthProfile(unsigned char nLevel, const char *szProfileName);
            virtual void SetAnimationProfile(unsigned char nLevel, const char *szProfileName);
            virtual const Anim::cAnimationProfile *RetAnimationProfile(unsigned char nLevel) const;
            virtual const cCharacterProfile *RetPtrProfile(unsigned char nLevel) const;
            virtual const RPG::cExplosivesSkillProfile *RetPtrExplosives(unsigned char nLevel) const;
            virtual const cStrengthSkillProfile *RetPtrStrength(unsigned char nLevel) const;
            virtual unsigned int RetSkeletonID(unsigned char nLevel) const;
            virtual float RetInitMinScale(unsigned char nLevel) const;
            virtual float RetInitMaxScale(unsigned char nLevel) const;

            CD2_LAYOUT_CHECKS(cCwTransCharacterPrototype,
                CD2_SIZE(cCwTransCharacterPrototype, 0x460)
                CD2_OFFSET(cCwTransCharacterPrototype, m_apTransBodyLODs, 0x330)
                CD2_OFFSET(cCwTransCharacterPrototype, m_apTransHeadLODs, 0x380)
                CD2_OFFSET(cCwTransCharacterPrototype, m_pAnimationProfileArray, 0x3D0)
                CD2_OFFSET(cCwTransCharacterPrototype, m_pProfileArray, 0x3E4)
                CD2_OFFSET(cCwTransCharacterPrototype, m_pExplosivesArray, 0x3F8)
                CD2_OFFSET(cCwTransCharacterPrototype, m_pStrengthArray, 0x40C)
                CD2_OFFSET(cCwTransCharacterPrototype, m_eSkeletonTypeIndex, 0x420)
                CD2_OFFSET(cCwTransCharacterPrototype, m_fInitMinScales, 0x434)
                CD2_OFFSET(cCwTransCharacterPrototype, m_fInitMaxScales, 0x448))
        };

        // CD2 0x82538150 forwards the prototype to constructor 0x82231358.
        cCwTransCharacter(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x82538078 / 0x82538088: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 primary slot 391; the embedded skill set owns the transformation flag.
        virtual bool IsTransformationRequired() const;
        virtual unsigned char RetAthleticLevel() const;
        virtual unsigned char RetExplosivesLevel() const;
        virtual unsigned char RetStrengthLevel() const;
        virtual unsigned char RetFirearmsLevel() const;
        virtual char RetActualSkill(unsigned int skill) const;
        virtual bool IsSkillAndBonusMaxed(unsigned int skill) const;
        virtual bool IsSkillMaxed(unsigned int skill) const;
        virtual bool vf384(unsigned int skill) const; // 0x825381E8; semantic virtual name remains unrecovered.
        virtual bool IsPowerUpActive(ePowerUp powerUp);
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual bool IsInDeathLimbo() const;
        virtual unsigned char vf406() const; // 0x82538220: reads m_byte2DA6.
        virtual void vf407(unsigned char value); // 0x82538228: stores m_byte2DA6.
        virtual void SetKilledByFriendly(bool friendly);
        virtual unsigned int RetLastVehicleHitID() const;
        virtual void SetLastVehicleHitID(unsigned int nVehicleID);
        virtual void TermClump(); // 0x82538EE8: qualified character-base forwarding.
        virtual void TriggerEnterWater(float fWaterLevel); // 0x82538880
        virtual void TriggerExitWater(float fWaterLevel); // 0x82538888
        virtual float vf132(); // CD2 0x8253BC08; inherited slot's purpose remains unrecovered.

        CD2_LAYOUT_CHECKS(cCwTransCharacter,
            CD2_SIZE(cCwTransCharacter, 0x2E00)
            CD2_OFFSET(cCwTransCharacter, m_nInvulnerableEnd, 0x2CC0)
            CD2_OFFSET(cCwTransCharacter, m_SkillSet, 0x2CC4)
            CD2_OFFSET(cCwTransCharacter, m_nPowerUpStatus, 0x2D64)
            CD2_OFFSET(cCwTransCharacter, m_bInDeathLimbo, 0x2DA4)
            CD2_OFFSET(cCwTransCharacter, m_bKilledByFriendly, 0x2DA5)
            CD2_OFFSET(cCwTransCharacter, m_byte2DA6, 0x2DA6)
            CD2_OFFSET(cCwTransCharacter, m_nLastVehicleHitID, 0x2DD0)
            CD2_OFFSET(cCwTransCharacter, m_fLastVehicleHitTimer, 0x2DD4))
    };
}

#endif // CHARACTER_CCWTRANSCHARACTER_H
