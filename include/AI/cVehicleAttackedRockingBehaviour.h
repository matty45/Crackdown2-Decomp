#include "gom/object_prototype.h"
#ifndef AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H
#define AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCBehaviour.h"
#include "AI/cChaseBehaviour.h"
#include "cd2/layout.h"

namespace AI
{
    class cVehicleAttackedRockingBehaviour : public NPCBehaviour
    {
    public:
        // RuffKing's sub-states.
        enum eSubState
        {
            eSubNull = 0,
            eSubIdle = 1,
            eSubRocking = 2,
        };
        // CD2 table 0x8200A6F0 has 99 primary slots: RuffKing's three new ones, in its order. 97 (0x824CF9B8) stores the
        // state, as RuffKing's EnterState does.
        virtual void ChangeState(eSubState eState); // primary slot 96
        virtual void EnterState(eSubState eState); // primary slot 97
        virtual void ExitState(); // primary slot 98

        // CD2 spawning initializer 0x82F9A5F8 names placement factory 0x824cf790.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleAttackedRockingBehaviourClass;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824CF790), which calls
        // NPCBehaviour's constructor (0x824A89C8) out of line and then sets the field below (name ours).
        __forceinline cVehicleAttackedRockingBehaviour() : m_eState(eSubIdle) {}

        // CD2's MakeNew (0x824CF6C8) allocates 0xB0, calls NPCBehaviourPrototype's constructor (0x824A8608) with the
        // packet, stores this prototype's vptrs (at 0 and 0x18) and the six float defaults below (RuffKing's names, at its
        // offsets).
        class cVehicleAttackedRockingBehaviourPrototype : public NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew.
            __forceinline cVehicleAttackedRockingBehaviourPrototype(const RWS::CAttributePacket &packet)
                : NPCBehaviourPrototype(packet), m_fMinRockInterval(0.3f), m_fMaxRockInterval(3.0f),
                  m_fEffectiveAttackRadius(2.0f), m_fMinForceToApply(1000.0f), m_fMaxForceToApply(5000.0f),
                  m_fForceApplicationDuration(4.0f) {}

        private:
            friend class cVehicleAttackedRockingBehaviour;
            float m_fMinRockInterval;           // 0x90
            float m_fMaxRockInterval;           // 0x94
            float m_fEffectiveAttackRadius;     // 0x98
            float m_fMinForceToApply;           // 0x9C
            float m_fMaxForceToApply;           // 0xA0
            float m_fForceApplicationDuration;  // 0xA4
            unsigned char m_unmodelledA8[0xB0 - 0xA8];

            // CD2: cVehicleAttackedRockingBehaviourPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824CFE18
        private:
            CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviourPrototype,
                CD2_SIZE(cVehicleAttackedRockingBehaviourPrototype, 0xB0)
                CD2_OFFSET(cVehicleAttackedRockingBehaviourPrototype, m_fMinRockInterval, 0x90)
                CD2_OFFSET(cVehicleAttackedRockingBehaviourPrototype, m_fForceApplicationDuration, 0xA4))
        };
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        // RuffKing's two members, 0x40 lower in CD2: OnEnter (0x824CF940) clears the timer at +0xC4 and Update
        // (0x824CF9C0) counts it down in the rocking state.
        eSubState m_eState;     // 0xC0
        float m_fCurrentTimer;  // 0xC4

        // RuffKing's helpers. CD2 expands the prototype getter and the rocking update into Update (0x824CF9C0) and
        // calls RockDrivenVehicle (0x824CFAB0).
        cVehicleAttackedRockingBehaviourPrototype *RetRockingPrototype()
        {
            return static_cast<cVehicleAttackedRockingBehaviourPrototype *>(m_pPrototype);
        }
        void OnUpdateRocking(float fDeltaTime);
        void RockDrivenVehicle();

        // 0xD0: the size the class registrar gives.
        CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviour,
            CD2_SIZE(cVehicleAttackedRockingBehaviour, 0xD0)
            CD2_OFFSET(cVehicleAttackedRockingBehaviour, m_eState, 0xC0)
            CD2_OFFSET(cVehicleAttackedRockingBehaviour, m_fCurrentTimer, 0xC4))

    public:
        // CD2 table 0x8200A6F0 differs from NPCBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824CF940
        virtual void Update(float fDeltaTime); // slot 71: 0x824CF9C0
    };
}

#endif

