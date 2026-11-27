// AI::cCharacterBrain (Crackdown 2): STAND-IN for the AI brain a character interface drives (cCharacterEntityIF's
// m_pCharacterBrain, 0x508). RuffKing's class (Kaim::CBrain base) gives the names of the flags CD2's script methods
// on cCharacterEntityIF set and read: "SetAiming" (0x823F4748) stores the byte at 0x20, "CrouchImmediately" /
// "UncrouchImmediately" (0x823F4718 / 0x823F4728) set and clear 0x21 and "IsTryingToCrouch" (0x823F4738) returns it,
// "DropImmediately" (0x823F46F8) clears 0x23 and "ExitVehicleImmediately" (0x823F4708) clears 0x24, which the
// ForceIntoVehicle/ForceOutOfVehicle overrides (0x823F46C0 / 0x823F46D0) set and clear. RuffKing has the same flags in
// the same order four bytes later (m_bAiming 0x24, m_bCrouching, m_bCovering, m_bCarrying, m_bInVehicle 0x28). CD2
// inlines each accessor, so they are inline here. The Kaim::CBrain base and the storage before 0x20 are not modelled.
// Agents (RuffKing's names): cCharacterEntityIF::SetActiveAgent (0x823F4758) expands the brain's SetActiveAgent on
// m_pActiveAgent (0x38; RuffKing's +0x34) and, unlike RuffKing, skips an agent that is already active and counts the
// changes in the word at 0x3C (name ours). The CreateAgent instances (0x823F5790 for IdleAgent, ...) search and extend
// m_vpAgentCache, whose element pointer is at 0x78 (the vector at 0x74).
#ifndef AI_CCHARACTERBRAIN_H
#define AI_CCHARACTERBRAIN_H

#include "AI/cAgent.h"
#include "fun_runtime/vector.h"
#include "cd2/memory.h"
#include "cd2/layout.h"

namespace AI
{
    class cCharacterBrain
    {
    public:
        bool IsTryingToCrouch() { return m_bCrouching; }
        void CrouchImmediately() { m_bCrouching = true; }
        void UncrouchImmediately() { m_bCrouching = false; }
        void DropImmediately() { m_bCarrying = false; }
        void SetAiming(bool bAiming) { m_bAiming = bAiming; }
        void SetInVehicle(bool bInVehicle) { m_bInVehicle = bInVehicle; }

        struct tAgentCacheBlock
        {
            cAgent *pAgent;                 // 0x0
            unsigned short nAgentTypeID;    // 0x4
        };

        // RuffKing's, out of line there; CD2 expands it into every CreateAgent instance.
        __forceinline cAgent *RetAgent(unsigned short nAgentTypeID) const
        {
            for (Fun_Runtime::cVector<tAgentCacheBlock>::const_iterator it = m_vpAgentCache.begin();
                 it != m_vpAgentCache.end(); ++it)
            {
                if (it->nAgentTypeID == nAgentTypeID)
                    return it->pAgent;
            }
            return 0;
        }

        // RuffKing's (cCharacterBrain.h); CD2 instantiates it in cCharacterEntityIF's object (0x823F5790 for
        // cIdleAgent, ...): look the agent type up, else create, reinitialise and cache one.
        template <class T> __forceinline T *RetAgent() const
        {
            return static_cast<T *>(RetAgent(T::StaticAgentClassID()));
        }
        template <class T> T *CreateAgent()
        {
            T *pAgent = RetAgent<T>();
            if (pAgent == 0)
            {
                pAgent = new T(this);
                pAgent->ReInit();
                tAgentCacheBlock block;
                block.pAgent = pAgent;
                block.nAgentTypeID = T::StaticAgentClassID();
                m_vpAgentCache.push_back(block);
            }
            return pAgent;
        }
        // RuffKing's (out of line there); CD2's callers (cCharacterEntityIF slots 105/106) expand it.
        cAgent *RetActiveAgent() const { return m_pActiveAgent; }
        // RuffKing's (out of line there); the "ClearBrainState" script method (0x823F47D8) expands it.
        void ClearActiveAgent()
        {
            if (m_pActiveAgent)
            {
                m_pActiveAgent->OnExit();
                m_pActiveAgent = 0;
            }
        }
        // __forceinline: CD2 expands it into cCharacterEntityIF::SetActiveAgent, which /Ob1 declines for a plain inline.
        __forceinline void SetActiveAgent(cAgent *pAgent)
        {
            if (pAgent != m_pActiveAgent)
            {
                if (m_pActiveAgent)
                    m_pActiveAgent->OnExit();
                m_pActiveAgent = pAgent;
                ++m_nActiveAgentChanges;
                pAgent->OnEnter();
            }
        }

    private:
        unsigned char m_unmodelled0[0x20];
        bool m_bAiming;                 // 0x20
        bool m_bCrouching;              // 0x21
        bool m_bCovering;               // 0x22
        bool m_bCarrying;               // 0x23
        bool m_bInVehicle;              // 0x24
        unsigned char m_unmodelled25[0x38 - 0x25];
        cAgent *m_pActiveAgent;         // 0x38
        unsigned int m_nActiveAgentChanges; // 0x3C
        unsigned char m_unmodelled40[0x74 - 0x40];
        Fun_Runtime::cVector<tAgentCacheBlock> m_vpAgentCache; // 0x74

        CD2_LAYOUT_CHECKS(cCharacterBrain,
            CD2_OFFSET(cCharacterBrain, m_bAiming, 0x20)
            CD2_OFFSET(cCharacterBrain, m_bCrouching, 0x21)
            CD2_OFFSET(cCharacterBrain, m_bCarrying, 0x23)
            CD2_OFFSET(cCharacterBrain, m_bInVehicle, 0x24)
            CD2_OFFSET(cCharacterBrain, m_pActiveAgent, 0x38)
            CD2_OFFSET(cCharacterBrain, m_nActiveAgentChanges, 0x3C)
            CD2_OFFSET(cCharacterBrain, m_vpAgentCache, 0x74))
    };
}

#endif // AI_CCHARACTERBRAIN_H
