// STAND-IN: RuffKing NPCArmedBehaviour derives from NPCBehaviour. CD2's
// StaticCreateClass (0x824A7E80) gives size 0xF0; fields after the 0xC0 base are unmodelled.
#ifndef AI_NPCARMEDBEHAVIOUR_H
#define AI_NPCARMEDBEHAVIOUR_H
#include "AI/NPCBehaviour.h"
namespace AI
{
    class NPCArmedBehaviour : public NPCBehaviour
    {
    public:
        // CD2 constructor 0x824A8070 installs 132-slot table 0x821089B0. Names/signatures of these slots remain unrecovered.
        virtual void vf96(); // primary slot 96
        virtual void vf97(); // primary slot 97
        virtual void vf98(); // primary slot 98
        virtual void vf99(); // primary slot 99
        virtual void vf100(); // primary slot 100
        virtual void vf101(); // primary slot 101
        virtual void vf102(); // primary slot 102
        virtual void vf103(); // primary slot 103
        virtual void vf104(); // primary slot 104
        virtual void vf105(); // primary slot 105
        virtual void vf106(); // primary slot 106
        virtual void vf107(); // primary slot 107
        virtual void vf108(); // primary slot 108
        virtual void vf109(); // primary slot 109
        virtual void vf110(); // primary slot 110
        virtual void vf111(); // primary slot 111
        virtual void vf112(); // primary slot 112
        virtual void vf113(); // primary slot 113
        virtual void vf114(); // primary slot 114
        virtual void vf115(); // primary slot 115
        virtual void vf116(); // primary slot 116
        virtual void vf117(); // primary slot 117
        virtual void vf118(); // primary slot 118
        virtual void vf119(); // primary slot 119
        virtual void vf120(); // primary slot 120
        virtual void vf121(); // primary slot 121
        virtual void vf122(); // primary slot 122
        virtual void vf123(); // primary slot 123
        virtual void vf124(); // primary slot 124
        virtual void vf125(); // primary slot 125
        virtual void vf126(); // primary slot 126
        virtual void vf127(); // primary slot 127
        virtual void vf128(); // primary slot 128
        virtual void vf129(); // primary slot 129
        virtual void vf130(); // primary slot 130
        virtual void vf131(); // primary slot 131

        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x8381E770: set by the initializer 0x82F91630 from StaticCreateClass; RetClass and IsA read it.
        static const Fun_Runtime::cClass *ms_pNPCArmedBehaviourClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
    private:
        unsigned char m_unmodelledC0[0xF0 - 0xC0];
    public:
        // Out of line: CD2 0x824A8070 (it first calls NPCBehaviour's 0x824A89C8).
        NPCArmedBehaviour();
        // Inline and empty: the deleting destructor 0x824C17F0 (shared by CellGuard, CellMinigun, CellRocket and
        // Peacekeeper, identical code folded) restores this class's vtables (0x821089B0, which its constructor installs)
        // and calls ~cNonGameBase directly; NPCBehaviour's own destructor stores none (~cPedestrianBase, 0x824A8EB8).
        virtual ~NPCArmedBehaviour() {}
    private:
        CD2_LAYOUT_CHECKS(NPCArmedBehaviour, CD2_SIZE(NPCArmedBehaviour, 0xF0))

    public:
        // CD2 table 0x821089B0 differs from NPCBehaviour at these inherited slots.
        virtual void Slot72(); // slot 72: 0x824A7E70
        virtual void Slot79(); // slot 79: 0x824A82C8
        virtual void Slot85(); // slot 85: 0x824A8110
        virtual void Slot89(); // slot 89: 0x824A7E60

    public:
        // CD2 table 0x821089B0 differs from NPCBehaviour at these inherited slots.

    public:
        // CD2 table 0x821089B0: overrides relative to NPCBehaviour.
        virtual void OnEnter(); // slot 68: 0x824A81A8
        virtual void OnExit(); // slot 69: 0x824A8278
        virtual void Slot71(); // slot 71: 0x824A8330
    };
}
#endif
