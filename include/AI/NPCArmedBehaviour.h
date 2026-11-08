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
    };
}
#endif
