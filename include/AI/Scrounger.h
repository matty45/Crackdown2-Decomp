// CD2 constructor 0x824BABB0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/FreakBase.h"
#include "gom/object_prototype.h"
#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    // RuffKing: AI::ScroungerPrototype : FreakPrototype, 528 bytes. CD2's Scrounger::MakeNew (0x824BAA18) allocates
    // 0x210 and calls this constructor (0x824BC850), which calls FreakPrototype's (0x824B0B78).
    class ScroungerPrototype : public FreakPrototype
    {
    public:
        ScroungerPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelledB0[0x210 - 0xB0];

        CD2_LAYOUT_CHECKS(ScroungerPrototype,
            CD2_SIZE(ScroungerPrototype, 0x210))
    };

    class Scrounger : public AI::FreakBase
    {
    public:
        // CD2 table 0x82109CC8 has 183 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf179(); // primary slot 179
        virtual void vf180(); // primary slot 180
        virtual void vf181(); // primary slot 181
        virtual void vf182(); // primary slot 182

        // CD2 factory 0x824BAA80 forwards only this, without a prototype argument. CD2 0x824BABB0, out of line:
        // FreakBase's constructor (0x824ABD60), the class vptrs, then the word at 0x120 = 13.
        Scrounger();
        // CD2 spawning initializer 0x82F943C8 names placement factory 0x824baa80.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pScroungerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknown120; // 0x120 (name ours; the constructor sets 13)
        // Other own fields not recovered; 0x130 is the size its registrar and descriptor give.
        unsigned char m_unmodelled124[0x130 - 0x124];

        // CD2: Scrounger's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot85(); // 85: 0x824BAF98
    private:
        CD2_LAYOUT_CHECKS(Scrounger,
            CD2_SIZE(Scrounger, 0x130)
            CD2_OFFSET(Scrounger, m_nUnknown120, 0x120))

    public:
        // CD2 table 0x82109CC8 differs from FreakBase at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824BAC28
        virtual void OnExit(); // slot 69: 0x824BADC0
        virtual void Slot71(); // slot 71: 0x824BBD30
        virtual void Slot72(); // slot 72: 0x824BAD08
        virtual void Slot89(); // slot 89: 0x824BAD88
        virtual void GetState(int n); // slot 100: 0x824BAE98
        virtual void vf120(); // slot 120: 0x824BB288
        virtual void vf141(); // slot 141: 0x824BBF78
        virtual void vf148(); // slot 148: 0x824BBCD8
        virtual void vf152(); // slot 152: 0x824BB540
        virtual void vf157(); // slot 157: 0x824BC7F8
        virtual void vf161(); // slot 161: 0x824BAE00
        virtual void vf165(); // slot 165: 0x824BBD38
        virtual void vf166(); // slot 166: 0x824BB008
        virtual void vf173(); // slot 173: 0x82564280

    public:
        // CD2 table 0x82109CC8 differs from FreakBase at these inherited slots.
        virtual void V102(); // slot 102: 0x824BACF0
        virtual void V104(); // slot 104: 0x824BB1B0
        virtual void V106(); // slot 106: 0x824BB7B8
        virtual void V108(); // slot 108: 0x824BB240
        virtual void Slot109(); // slot 109: 0x824BB560
        virtual void Slot110(); // slot 110: 0x824BB738
        virtual NPCTarget *GetTarget(); // slot 115: 0x824BB0A0
        virtual void V118(); // slot 118: 0x824BBCD0
    };
}

#endif
