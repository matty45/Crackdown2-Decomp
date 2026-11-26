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
#include "AI/AIBehaviour.h"

namespace Activity
{
    class cSquadMemberSpawnPoint;
}

namespace AI
{
    class cAiPlayer;
    class NPCTarget;

    class NPCBehaviour : public AIBehaviour
    {
    public:
        // CD2 constructor 0x824A89C8 installs the 96-slot table 0x82108C08.
        virtual void OnEnterReplicatedState(unsigned char);
        virtual void Slot73();
        virtual void OnEvent74(NPCTarget *t);
        virtual void OnEvent75(NPCTarget *t);
        virtual void Slot76();
        virtual void Slot77();
        virtual void Slot78();
        virtual void Slot79();
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // RuffKing OnCharacterEvent (cAgressiveResponseChaseBehaviour 0x824CAF68)
        virtual void Slot81();
        virtual void Slot82();
        virtual void Slot83();
        virtual void Slot84();
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &);
        // 86..95: RuffKing's names and order (its slots 55..64; CD2 has no StartSequence after them). The defaults in
        // CD2's table 0x82108C08 agree: 87 stores m_pAmbientTarget (0x824A7DE0), 91 returns the zero vector, 93
        // returns 1000 (Goliath's 0x824B12F0: 3500), 94 and 95 return true.
        virtual void SetSpawnAction(unsigned char);
        virtual void SetAmbientTarget(Activity::cSquadMemberSpawnPoint *pTarget) { m_pAmbientTarget = pTarget; }
        virtual void NotifySquadMemberDead();
        virtual unsigned char GetStateReplicationInfo() const;
        virtual bool HasControlsVelocityOverride() const;
        virtual const Fun_Runtime::Vec3 &GetControlsVelocityOverride() const;
        virtual void SetControlsVelocityOverride(const Fun_Runtime::Vec3 &);
        virtual unsigned int RetCorpseFadeOutTimeMillis() const { return 1000; }
        virtual bool ShouldLockVehicleOwnership() const;
        virtual bool CanBeAttackedByNPC() const;

        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
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
        // Compiler-generated (RuffKing). CD2's table 0x82108C08 shares deleting
        // wrapper 0x824A4C30 without any NPC vtable restoration.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // Defined in the class body: RuffKing emits NPCBehaviour::RetClassName in NPCArmedBehaviour.obj, and CD2 has it
        // (with the two defaults above) at the start of NPCArmedBehaviour's code (0x824A7DD0..0x824A7DE8).
        virtual const char *RetClassName() const { return "NPCBehaviour"; }

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
