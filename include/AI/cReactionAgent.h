// AI::cReactionAgent (Crackdown 2): STAND-IN. RuffKing's cReactionAgent : cAgent (AI/Agents/cReactionAgent.h) with its
// fields 8 bytes later (0x10 after its 16-byte vectors), after CD2's 0x10-byte cAgent. CD2's
// CreateAgent<cReactionAgent> (0x823F7770) allocates 0x60 bytes and expands RuffKing's constructor: reaction 0xB and
// flags 0xF, the reaction point from ZeroVec (three floats and w = 1), a zero source velocity, the flags clear,
// chance 0.65, timers 0; then it installs table 0x820FDF30 (RetAgentName 0x8241AE78 returns "cReactionAgent"; slot
// 14, RetAgentClassID, is 0x8241AE30). CD2 does not set RuffKing's m_bSuccess (0x49 here), so it is not modelled. The
// table overrides RetAgentStatus (slot 2, 0x8241AE98), Think (5, 0x821EADF0), OnEnter (6, 0x8241AEA0), OnExit (7,
// 0x8241AF60) and EventAnimation (9, 0x8241B6C0).
#ifndef AI_CREACTIONAGENT_H
#define AI_CREACTIONAGENT_H

#include "AI/cAgent.h"
#include "fun_runtime/vec3.h"

namespace AI
{
    class cReactionAgent : public cAgent
    {
    public:
        // __forceinline: CD2 expands it into CreateAgent<cReactionAgent>, which /Ob1 declines for a plain inline.
        __forceinline cReactionAgent(cCharacterBrain *pBrain)
            : cAgent(pBrain), m_nReaction(0xB), m_nReactionState(0), m_nReactionFlags(0xF),
              m_vReactionPoint(Fun_Runtime::ZeroVec), m_bHasSourceVelocity(false), m_bForceReaction(false),
              m_fReactionChance(0.65f), m_bFinished(false), m_fInitialWait(0.0f), m_fCurrentTimer(0.0f)
        {
        }
        // RuffKing's: the type's ID, allocated on first use (CD2 expands it into CreateAgent and RetAgentClassID).
        static unsigned short StaticAgentClassID()
        {
            static unsigned short s_nAgentClassID = AllocAgentClassID();
            return s_nAgentClassID;
        }
        virtual const char *RetAgentName();
        virtual unsigned int RetAgentStatus() const;
        virtual void Think();
        virtual void OnEnter();
        virtual void OnExit();
        virtual void EventAnimation(const CHARACTER::etActionTypesEnum &eType, int nBaseState, short nEventID);
        virtual unsigned short RetAgentClassID();
        // RuffKing's setters (out of line there); cCharacterEntityIF::Reaction (0x823F2A40) expands them.
        void SetReactionSourceVelocity(const Fun_Runtime::Vec3 &vVelocity)
        {
            m_vReactionSourceVelocity = vVelocity;
            m_bHasSourceVelocity = true;
        }
        void SetReactionPos(const Fun_Runtime::Vec3 &vPos) { m_vReactionPoint = vPos; }
        void SetReaction(char nReaction) { m_nReaction = nReaction; }
        void SetReactionFlags(unsigned int nFlags) { m_nReactionFlags = nFlags; }
        void SetReactionChance(float fChance) { m_fReactionChance = fChance; }

    private:
        char m_nReaction;                                       // 0x10
        char m_nReactionState;                                  // 0x11
        unsigned int m_nReactionFlags;                          // 0x14
        Fun_Runtime::Vec3 m_vReactionPoint;                     // 0x20
        Fun_Runtime::Vec3 m_vReactionSourceVelocity;            // 0x30
        bool m_bHasSourceVelocity;                              // 0x40
        bool m_bForceReaction;                                  // 0x41
        float m_fReactionChance;                                // 0x44
        bool m_bFinished;                                       // 0x48
        float m_fInitialWait;                                   // 0x4C
        float m_fCurrentTimer;                                  // 0x50

        CD2_LAYOUT_CHECKS(cReactionAgent,
            CD2_SIZE(cReactionAgent, 0x60)
            CD2_OFFSET(cReactionAgent, m_nReactionFlags, 0x14)
            CD2_OFFSET(cReactionAgent, m_vReactionPoint, 0x20)
            CD2_OFFSET(cReactionAgent, m_bHasSourceVelocity, 0x40)
            CD2_OFFSET(cReactionAgent, m_fReactionChance, 0x44)
            CD2_OFFSET(cReactionAgent, m_bFinished, 0x48)
            CD2_OFFSET(cReactionAgent, m_fCurrentTimer, 0x50))
    };
}

#endif // AI_CREACTIONAGENT_H
