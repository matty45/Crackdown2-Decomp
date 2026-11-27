// AI::cExitVehicleAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cExitVehicleAgent> (0x823F96E8) allocates 0x1C
// bytes, builds a cAgent and installs table 0x820FE64C (RetAgentName 0x82423D48 returns "ExitVehicleAgent"; slot 14,
// RetAgentClassID, is 0x82423D00). Its fields are RuffKing's (AI/Agents/VehicleAgents/cExitVehicleAgent.h, 8 bytes
// earlier there) without m_nStatus: CD2 clears the two floats at 0x10/0x14 and the flags at 0x18/0x19, and keeps
// cAgent's RetAgentStatus (slot 2 is 0x8288FB78). It overrides Think, OnEnter, OnExit, EventTrigger and EventAnimation
// (slots 5..9: 0x82423FC0, 0x82423DF8, 0x82423E18, 0x82424228, 0x82424158).
#ifndef AI_CEXITVEHICLEAGENT_H
#define AI_CEXITVEHICLEAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cExitVehicleAgent : public cAgent
    {
    public:
        cExitVehicleAgent(cCharacterBrain *pBrain)
            : cAgent(pBrain), m_fLastAttemptTime(0.0f), m_nNumAttempts(0.0f), m_bTriggered(false), m_bAttempting(false)
        {
        }
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual void Think();
        virtual void OnEnter();
        virtual void OnExit();
        virtual void EventTrigger(CHARACTER::eControllerEventType eEventType,
            CHARACTER::eControllerEventSubType eEventSubType,
            CHARACTER::eControllerEvents eEvent);
        virtual void EventAnimation(const CHARACTER::etActionTypesEnum &eType, int nBaseState, short nEventID);
        virtual unsigned short RetAgentClassID();

    private:
        float m_fLastAttemptTime;                               // 0x10
        float m_nNumAttempts;                                   // 0x14
        bool m_bTriggered;                                      // 0x18
        bool m_bAttempting;                                     // 0x19

        CD2_LAYOUT_CHECKS(cExitVehicleAgent,
            CD2_SIZE(cExitVehicleAgent, 0x1C)
            CD2_OFFSET(cExitVehicleAgent, m_fLastAttemptTime, 0x10)
            CD2_OFFSET(cExitVehicleAgent, m_nNumAttempts, 0x14)
            CD2_OFFSET(cExitVehicleAgent, m_bTriggered, 0x18)
            CD2_OFFSET(cExitVehicleAgent, m_bAttempting, 0x19))
    };
}

#endif // AI_CEXITVEHICLEAGENT_H
