// AI::cCharacterEntityIF (Crackdown 2): STAND-IN, sized to CD2. cClass(0x5F1, "cCharacterEntityIF", 0x540); its
// constructor 0x823EF240 calls cCharacterInterface's (0x8254EC78). Only the accessors below are modelled;
// storage outside their observed fields remains unknown. The names of the added fields and accessors are
// stand-ins: 0x823EC160/0x823EC168 read/write a word at 0x51C; 0x823EC1F8..0x823EC230 write/read the four
// bytes at 0x534..0x537; 0x823EC028 writes the byte at 0x539. Their semantic names are not established.
// 0x823EBF90 and 0x823EBF88 return addresses within the object at 0x480 and 0x4B0; those regions remain
// untyped storage. 0x823EC038 reads a word at 0x50C and returns its least-significant byte.
// m_pAIEntity (0x504; RuffKing's name and type, at 0xF8 there): cAiPlayer::RetName (0x823EB508) returns its m_name, as
// RuffKing's cAiPlayer::RetName returns m_pAIEntity's; the accessors below read the entity's script-named fields
// (AI/cCharacterEntity.h).
#ifndef AI_CCHARACTERENTITYIF_H
#define AI_CCHARACTERENTITYIF_H

#include "CHARACTER/cCharacterInterface.h"
#include "AI/cCharacterEntity.h"

namespace AI
{
    class cCharacterEntityIF : public CHARACTER::cCharacterInterface
    {
    private:
        unsigned char m_padC0[0x480 - 0xC0];
    protected:
        unsigned char m_storage480[0x4B0 - 0x480];
        unsigned char m_storage4B0[0x4F8 - 0x4B0];
        int m_n4F8;                             // 0x4F8..0x500: written by cAiPlayer's slot 125 (0x823E92B8);
        int m_n4FC;                             // nothing names them
        int m_n500;
        cCharacterEntity *m_pAIEntity;          // 0x504
        unsigned char m_pad508[0x50C - 0x508];
        unsigned int m_word50C;
    private:
        unsigned char m_pad510[0x51C - 0x510];
    protected:
        unsigned int m_word51C;
    private:
        unsigned char m_pad520[0x534 - 0x520];
    protected:
        unsigned char m_byte534;
        unsigned char m_byte535;
        unsigned char m_byte536;
        unsigned char m_byte537;
    private:
        unsigned char m_pad538;
    protected:
        unsigned char m_byte539;
    private:
        unsigned char m_pad53A[0x540 - 0x53A];

    public:
        static const Fun_Runtime::cClass *ms_pcCharacterEntityIFClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x823EF240 is the no-argument constructor called by 0x823EBF10.
        cCharacterEntityIF();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        void *GetStorage480();
        void *GetStorage4B0();
        unsigned char GetWord50CLowByte() const;
        unsigned int GetWord51C() const;
        void SetWord51C(unsigned int value);
        void SetByte534(unsigned char value);
        void SetByte535(unsigned char value);
        void SetByte536(unsigned char value);
        void SetByte537(unsigned char value);
        unsigned char GetByte534() const;
        unsigned char GetByte535() const;
        unsigned char GetByte536() const;
        unsigned char GetByte537() const;
        void SetByte539(unsigned char value);
        virtual const char *RetClassName() const;
        const char *RetMovementType() const;
        const char *RetPerceptionOptions() const;
        const char *RetFaceTarget() const;
        const char *RetAttackState() const;
        const char *RetState() const;
        void *GetPtr504A0() const;
        void *GetPtr504B0() const;
        float GetFloat504_90() const;
        float GetFloat504_98() const;
        float GetFloat504_9C() const;
        unsigned char GetBool38_50() const;
        unsigned char CheckField548() const;
        float GetFloatConditional() const;

        CD2_LAYOUT_CHECKS(cCharacterEntityIF,
            CD2_SIZE(cCharacterEntityIF, 0x540)
            CD2_OFFSET(cCharacterEntityIF, m_storage480, 0x480)
            CD2_OFFSET(cCharacterEntityIF, m_storage4B0, 0x4B0)
            CD2_OFFSET(cCharacterEntityIF, m_n4F8, 0x4F8)
            CD2_OFFSET(cCharacterEntityIF, m_pAIEntity, 0x504)
            CD2_OFFSET(cCharacterEntityIF, m_word50C, 0x50C)
            CD2_OFFSET(cCharacterEntityIF, m_word51C, 0x51C)
            CD2_OFFSET(cCharacterEntityIF, m_byte534, 0x534)
            CD2_OFFSET(cCharacterEntityIF, m_byte535, 0x535)
            CD2_OFFSET(cCharacterEntityIF, m_byte536, 0x536)
            CD2_OFFSET(cCharacterEntityIF, m_byte537, 0x537)
            CD2_OFFSET(cCharacterEntityIF, m_byte539, 0x539))
    };
}

#endif // AI_CCHARACTERENTITYIF_H
