#include "fun_runtime/class.h"
// STAND-IN: Burn/RuffKing base order; CD2 cBody debug interface starts at 0x120.
#ifndef CD2_GOM_GAME_BASE_H
#define CD2_GOM_GAME_BASE_H
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
__declspec(align(16)) class cGameBase : public RWS::CSystemCommands, public cNonGameBase
{
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsAlive() const;
        // Name, base and size (224 bytes) from RuffKing. CD2's constructor (0x82652850) calls GOM::cObjectPrototype's;
        // cBodyPrototype's constructor (0x826845A8) calls it, and cPhantomBody::MakeNew (0x8268A368) allocates 0xF0
        // for a prototype that adds one word at 0xE0.
        class cGameBasePrototype : public cNonGameBase::cNonGameBasePrototype
        {
        public:
            cGameBasePrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled70[0xE0 - 0x70];
        };

        // CD2 0x82650268 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGameBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;

public:
    // CD2 script registration names the setter at 0x824C83F8; RuffKing names the member.
    void SetFullHealth(float);
    // RuffKing's three health members; CD2's script wrapper 0x8254E8E8 reads 0x110/0x114/0x118.
    float RetHealthFraction() const;
    // Inline: cBody's (0x826837D8) and cPhantomBody's (0x8268A578) destructors restore cGameBase's tables and then
    // call ~cNonGameBase directly.
    virtual ~cGameBase() {}
    // Called by cBody's overrides: Init(packet) 0x82323A98, Term 0x82650EB8, Reinitialise 0x82651008 and TermForReuse
    // 0x82650F80.
    // CD2 0x822C4BE0: cGameBase table 0x8212CA20 slot 1; cBody's override (0x826838B0) tail-calls it.
    virtual void HandleAttributes(const RWS::CAttributePacket &);
    virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // CD2 0x826508E0
    virtual Fun_Runtime::RetVal Term();
    virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);
    virtual Fun_Runtime::RetVal TermForReuse();
    // Primary slots 68..140: cGameBase's own virtuals. CD2's cGameBase table (0x8212CA20, stored by the constructor
    // 0x82650610) has 141 slots. Names are not recovered yet; vfN is the slot index (the SlotN names cNonGameBase
    // uses drift by one from slot 32, so they are not reused here).
    virtual void vf68(); virtual void vf69(); virtual void vf70(); virtual void vf71(); virtual void vf72(); virtual void vf73();
    virtual void vf74(); virtual void vf75(); virtual void vf76(); virtual void vf77(); virtual void vf78(); virtual void vf79();
    virtual void vf80(); virtual void vf81(); virtual void vf82(); virtual void vf83(); virtual void vf84(); virtual void vf85();
    virtual void vf86(); virtual void vf87(); virtual void vf88(); virtual void vf89(); virtual void vf90(); virtual void vf91();
    virtual void vf92(); virtual void vf93(); virtual void vf94(); virtual void vf95(); virtual void vf96(); virtual void vf97();
    virtual void vf98(); virtual void vf99(); virtual void vf100(); virtual void vf101(); virtual void vf102(); virtual void vf103();
    virtual void vf104(); virtual void vf105(); virtual void vf106(); virtual void vf107(); virtual void vf108(); virtual void vf109();
    virtual void vf110(); virtual void vf111(); virtual void vf112(); virtual void vf113(); virtual void vf114(); virtual void vf115();
    virtual void vf116(); virtual void vf117(); virtual void vf118(); virtual void vf119(); virtual void vf120(); virtual void vf121();
    virtual void vf122(); virtual void vf123(); virtual void vf124(); virtual void vf125(); virtual void vf126(); virtual void vf127();
    virtual void vf128(); virtual void vf129(); virtual void vf130(); virtual void vf131(); virtual void vf132(); virtual void vf133();
    virtual void vf134(); virtual void vf135(); virtual void vf136(); virtual void vf137(); virtual void vf138(); virtual void vf139();
    virtual void vf140();
private:
    unsigned char m_unknown7C[0x110 - 0x7C];
    float m_fHealth;
    float m_fFullHealth;
    float m_fFullHealthMultiplier;
    unsigned char m_unknown11C[0x120 - 0x11C];
    CD2_LAYOUT_CHECKS(cGameBase,
        CD2_SIZE(cGameBase, 0x120)
        CD2_OFFSET(cGameBase, m_fHealth, 0x110)
        CD2_OFFSET(cGameBase, m_fFullHealth, 0x114)
        CD2_OFFSET(cGameBase, m_fFullHealthMultiplier, 0x118))
};
#endif
