// STAND-IN: RuffKing NPCBehaviour.h names the base, primary GUID and secondary
// weapon vector. CD2 constructor 0x824A8608 and destructor 0x824A8690 confirm
// their offsets, the vector's three pointers and complete size 0x90.
#ifndef AI_NPCBEHAVIOURPROTOTYPE_H
#define AI_NPCBEHAVIOURPROTOTYPE_H

#include "AI/AIBehaviour.h"
#include "fun_runtime/vector.h"

namespace AI
{
    class NPCBehaviourPrototype : public AIBehaviour::AIBehaviourPrototype
    {
    public:
        NPCBehaviourPrototype(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual const RWS::RWSGUID &RetPrimaryWeapon() const;
        // Existing chase-profile entry points; their original wrapper names remain unresolved.
        void HandleAttributesBase(const RWS::CAttributePacket &);
        void HandleAttributesNPC(const RWS::CAttributePacket &);

        RWS::RWSGUID mPrimary;
        Fun_Runtime::cVector<RWS::RWSGUID> mSecondaries;

        CD2_LAYOUT_CHECKS(NPCBehaviourPrototype,
            CD2_SIZE(NPCBehaviourPrototype, 0x90)
            CD2_OFFSET(NPCBehaviourPrototype, mPrimary, 0x70)
            CD2_OFFSET(NPCBehaviourPrototype, mSecondaries, 0x80))
    };
}
#endif
