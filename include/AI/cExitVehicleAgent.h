// AI::cExitVehicleAgent (Crackdown 2): STAND-IN. CD2's CreateAgent<cExitVehicleAgent> (0x823F96E8) allocates 0x1C
// bytes, builds a cAgent and installs table 0x820FE64C (RetAgentName 0x82423D48 returns "ExitVehicleAgent"; slot 14,
// RetAgentClassID, is 0x82423D00). Its own fields are not modelled.
#ifndef AI_CEXITVEHICLEAGENT_H
#define AI_CEXITVEHICLEAGENT_H

#include "AI/cAgent.h"

namespace AI
{
    class cExitVehicleAgent : public cAgent
    {
    public:
        cExitVehicleAgent(cCharacterBrain *pBrain) : cAgent(pBrain) {}
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned short RetAgentClassID();

    private:
        unsigned char m_unmodelled10[0x1C - 0x10];

        CD2_LAYOUT_CHECKS(cExitVehicleAgent,
            CD2_SIZE(cExitVehicleAgent, 0x1C))
    };
}

#endif // AI_CEXITVEHICLEAGENT_H
