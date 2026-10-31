// CHARACTER::cCwTransCharacter (Crackdown 2 only; Burn calls it cPlayerCharacter): STAND-IN, sized to CD2. Evidence:
// its StaticCreateClass builds cClass(0x6A1, "cCwTransCharacter", 0x2E00); its constructor 0x82231358 (its
// SpawnFromPrototype tail-calls it) calls cCharacter's constructor 0x82543408. CD2's cFrontEndAgent also derives from
// it.
// Accessor evidence from CD2: 0x82538170 reads byte 0x2D20; 0x825381F0 tests a bit in
// halfword 0x2D64; 0x82538218..0x82538230 read/write bytes 0x2DA4..0x2DA6;
// 0x82538238 reads word 0x2DD0. These field and method names are ours. The full
// primary virtual interface is not modelled; these accessors are declared directly.
#ifndef CHARACTER_CCWTRANSCHARACTER_H
#define CHARACTER_CCWTRANSCHARACTER_H

#include "CHARACTER/cCharacter.h"
#include "gom/object_prototype.h"

namespace CHARACTER
{
    class cCwTransCharacter : public cCharacter
    {
    private:
        unsigned char m_pad2CC0[0x2D20 - 0x2CC0];
        unsigned char m_byte2D20;
        unsigned char m_pad2D21[0x2D64 - 0x2D21];
        unsigned short m_flags2D64;
        unsigned char m_pad2D66[0x2DA4 - 0x2D66];
        unsigned char m_byte2DA4;
        unsigned char m_byte2DA5;
        unsigned char m_byte2DA6;
        unsigned char m_pad2DA7[0x2DD0 - 0x2DA7];
        unsigned int m_word2DD0;
        unsigned char m_pad2DD4[0x2E00 - 0x2DD4];

    public:
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
        unsigned char GetByte2D20() const;
        bool TestFlag2D64(unsigned int bit) const;
        unsigned char GetByte2DA4() const;
        unsigned char GetByte2DA6() const;
        void SetByte2DA6(unsigned char value);
        void SetByte2DA5(unsigned char value);
        unsigned int GetWord2DD0() const;

        CD2_LAYOUT_CHECKS(cCwTransCharacter,
            CD2_SIZE(cCwTransCharacter, 0x2E00)
            CD2_OFFSET(cCwTransCharacter, m_byte2D20, 0x2D20)
            CD2_OFFSET(cCwTransCharacter, m_flags2D64, 0x2D64)
            CD2_OFFSET(cCwTransCharacter, m_byte2DA4, 0x2DA4)
            CD2_OFFSET(cCwTransCharacter, m_byte2DA5, 0x2DA5)
            CD2_OFFSET(cCwTransCharacter, m_byte2DA6, 0x2DA6)
            CD2_OFFSET(cCwTransCharacter, m_word2DD0, 0x2DD0))
    };
}

#endif // CHARACTER_CCWTRANSCHARACTER_H
