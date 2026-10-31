// AI::NPCBehaviour (Crackdown 2): STAND-IN. Size 0xC0: its registrar's size, and AI::cPedestrianBase's first own field
// (m_nState, RuffKing's 0x100) is at 0xC0. Its constructor is 0x824A89C8 (cPedestrianBase's calls it). Fields not
// modelled.
#ifndef AI_NPCBEHAVIOUR_H
#define AI_NPCBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"

namespace AI
{
    class NPCBehaviour : public cNonGameBase
    {
    private:
        unsigned char m_pad7C[0xC0 - 0x7C];

    public:
        static const Fun_Runtime::cClass *ms_pNPCBehaviourClass;

        NPCBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(NPCBehaviour,
            CD2_SIZE(NPCBehaviour, 0xC0))
    };
}

#endif
