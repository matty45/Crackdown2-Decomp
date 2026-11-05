// AI::NPCBehaviour (Crackdown 2): STAND-IN. Size 0xC0: its registrar's size, and AI::cPedestrianBase's first own field
// (m_nState, RuffKing's 0x100) is at 0xC0. Its constructor is 0x824A89C8 (cPedestrianBase's calls it). Fields from
// RuffKing (0xC0-0xF4 there, after its larger cNonGameBase); the constructor zeroes 0x7C, 0x80, both vectors and 0xB4 in
// CD2. The vectors make the class 16-byte aligned, which is why derived classes are padded to 0xD0 (TrainingPilot's 0xC1 bytes).
#ifndef AI_NPCBEHAVIOUR_H
#define AI_NPCBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace Activity
{
    class cSquadMemberSpawnPoint;
}

namespace AI
{
    class cAiPlayer;

    class NPCBehaviour : public cNonGameBase
    {
    public:
        // CD2 0x824A87A0 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();

    protected:
        cAiPlayer *m_pHost;
        bool m_bReactResupplyPointSet;
        Fun_Runtime::Vec3 m_vReactResupply;
        Fun_Runtime::Vec3 m_vRespawnHeading;
        float m_fInActivityTimer;
        Activity::cSquadMemberSpawnPoint *m_pAmbientTarget;

    public:
        static const Fun_Runtime::cClass *ms_pNPCBehaviourClass;

        NPCBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(NPCBehaviour,
            CD2_SIZE(NPCBehaviour, 0xC0)
            CD2_OFFSET(NPCBehaviour, m_pHost, 0x7C)
            CD2_OFFSET(NPCBehaviour, m_bReactResupplyPointSet, 0x80)
            CD2_OFFSET(NPCBehaviour, m_vReactResupply, 0x90)
            CD2_OFFSET(NPCBehaviour, m_vRespawnHeading, 0xA0)
            CD2_OFFSET(NPCBehaviour, m_fInActivityTimer, 0xB0)
            CD2_OFFSET(NPCBehaviour, m_pAmbientTarget, 0xB4))
    };
}

#endif
