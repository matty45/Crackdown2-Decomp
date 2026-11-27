// AI::cAgent (Crackdown 2): STAND-IN. The base of the AI brain's behaviour agents (RuffKing/Burn AI/Agents/cAgent.h:
// a vtable and m_pBrain at +4, 8 bytes). CD2's agents are 0x10 bytes: every inlined agent constructor (the
// CreateAgent instances in cCharacterEntityIF's object, 0x823F5790 for IdleAgent) stores the brain at +4, then 0 at
// +0xC and the Kaim::CHeuristicEuclidianDistance table (0x82000EF0) at +8, an embedded heuristic RuffKing's cAgent
// lacks (name ours). The deleting destructor shared by the agents without their own (0x82406A08) restores this class's
// table (0x820FCDF4) and the heuristic's Kaim::CObject table, so the destructor is user-declared and inline.
// CD2's table has 15 slots: RuffKing's 14 with RetAgentStatus and CanUseUpperBodyLookat swapped (cFaceAgent overrides
// slot 2 with RuffKing's RetAgentStatus body, 0x8240C948) and one more before the pure RetAgentClassID (slot 14).
// Slots 8 and 9 are RuffKing's EventTrigger and EventAnimation: CD2's cDropAgent and cSecondaryFireAgent override slot 8
// and test its three controller-event arguments (RuffKing's cThrowAgent and cExitVehicleAgent override EventTrigger),
// and cPrimaryFireAgent's slot 9 (0x8241A7D8) reads its first argument through a reference and sign-extends the third,
// as EventAnimation(const etActionTypesEnum &, int, short). RuffKing's ShowDestination, ShowDebugInfo and
// ReevaluatePath do not map one to one onto CD2's remaining empty slots 10..13, so those stay unnamed. The base RetAgentName (0x82405630) returns
// "Unnamed Brain State"; CD2 calls ReInit (slot 4) after creating an agent and OnExit/OnEnter (slots 7/6) when the
// brain changes its active agent.
#ifndef AI_CAGENT_H
#define AI_CAGENT_H

#include "Kaim/CHeuristicEuclidianDistance.h"
#include "CHARACTER/controllerevents.h"
#include "cd2/layout.h"

namespace AI
{
    class cCharacterBrain;

    class cAgent
    {
    public:
        cAgent(cCharacterBrain *pBrain) : m_pBrain(pBrain) {}
        virtual ~cAgent() {}
        virtual const char *RetAgentName();
        virtual unsigned int RetAgentStatus() const;
        virtual bool CanUseUpperBodyLookat() const;
        virtual void ReInit();
        virtual void Think();
        virtual void OnEnter();
        virtual void OnExit();
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual void EventAnimation(const CHARACTER::etActionTypesEnum &eType, int nBaseState, short nEventID);
        virtual void vf10();
        virtual void vf11();
        virtual void vf12();
        virtual void vf13();
        virtual unsigned short RetAgentClassID() = 0;

    protected:
        // RuffKing's; CD2 expands it into every agent's StaticAgentClassID (0x8240E070 for cIdleAgent). The counter
        // (0x830AB1CC) starts at 1.
        static unsigned short AllocAgentClassID() { return s_nNextAgentID++; }
        static unsigned short s_nNextAgentID;

        cCharacterBrain *m_pBrain;                          // 0x4
        Kaim::CHeuristicEuclidianDistance m_Heuristic;      // 0x8

        CD2_LAYOUT_CHECKS(cAgent,
            CD2_SIZE(cAgent, 0x10)
            CD2_OFFSET(cAgent, m_pBrain, 0x4)
            CD2_OFFSET(cAgent, m_Heuristic, 0x8))
    };
}

#endif // AI_CAGENT_H
