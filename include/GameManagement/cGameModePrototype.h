// STAND-IN: RuffKing names cGMMResource as the base. CD2 constructor 0x8283B2B8
// calls 0x828498C0 and initializes 0x60..0xF4. Its primary table 0x8215B0D8 has
// 42 slots; unidentified methods retain their slot indices. Storage is not yet recovered.
#ifndef GAMEMANAGEMENT_CGAMEMODEPROTOTYPE_H
#define GAMEMANAGEMENT_CGAMEMODEPROTOTYPE_H
#include "GameManagement/cGMMResource.h"
#include "GameManagement/game_types.h"
namespace GameManagement
{
    class cGameModePrototype : public cGMMResource
    {
    public:
        cGameModePrototype();
        virtual ~cGameModePrototype();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void vf11();
        virtual void vf12();
        virtual void vf13();
        virtual etGameModeType RetType() const;
        virtual void vf15();
        virtual void vf16();
        virtual void vf17();
        virtual void vf18();
        virtual void vf19();
        virtual void vf20();
        virtual void vf21();
        virtual void vf22();
        virtual void vf23();
        virtual void vf24();
        virtual void vf25();
        virtual void vf26();
        // CD2 concrete overrides at slot 27 return their localization string IDs.
        virtual int RetStringID() const;
        virtual void vf28();
        virtual void vf29();
        virtual void vf30();
        virtual void vf31();
        virtual void vf32();
        virtual void vf33();
        virtual unsigned int RetEndLimit(unsigned int) const;
        virtual unsigned int RetTimeLimit(unsigned int) const;
        virtual unsigned int RetDefaultEndLimit();
        virtual unsigned int RetDefaultTimeLimit();
        virtual float RetSpawnPointTimeOut() const;
        virtual void vf39();
        virtual void vf40();
        virtual void vf41();
    private:
        unsigned char m_unmodelled60[0xE0 - 0x60];
        // RuffKing names this 64-bit field; CD2 constructor stores it at 0xE0.
        unsigned long long m_nDataConfigFlags;
        unsigned char m_unmodelledE8[0xF8 - 0xE8];
        CD2_LAYOUT_CHECKS(cGameModePrototype,
            CD2_SIZE(cGameModePrototype, 0xF8)
            CD2_OFFSET(cGameModePrototype, m_nDataConfigFlags, 0xE0))
    };
}
#endif
