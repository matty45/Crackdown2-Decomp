// AI::cAgressiveResponseChaseBehaviour (CD2 size 0x140, registrar and StaticCreateClass).
// Primary vtable 0x8210B748 (installed by the placement factory 0x824C92B0) has 154 slots: 0..119 are
// cAgressiveResponseBase's (table 0x8210B510), 120..153 this class's own. RuffKing declares exactly 34 own virtuals
// (EnterGettingOut .. StartReaction, its slots 88..121); CD2's bodies line up with that order at slot + 32
// (ExitGettingOut 147 clears the base flag at 0xF5, ExitMoveToCover 148 tests m_bTransitioningToCover, ...).
// Own fields: RuffKing's order (cover point, vehicle safe pointer, seat, goal distance, ... prototype) at CD2's offsets
// from the factory's stores (0x10C..0x138); CD2 has three more words at 0x100..0x108 that the reference builds lack
// (their names are ours).
#ifndef AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H
#define AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "fun_runtime/safedeletablepointer.h"
#include "rws/attributes.h"
#include "AI/cAgressiveResponseBase.h"

namespace Vehicle { class cVehicle; }

namespace AI
{
    class cCoverPoint;

    class cAgressiveResponseChaseBehaviour : public cAgressiveResponseBase
    {
    public:
        enum eSubState
        {
            eState_ARCBFirstState = 7,
            eState_GettingOutOfVehicle = 7,
            eState_MoveAdvance = 8,
            eState_MoveRetreat = 9,
            eState_MoveToCover = 10,
            eState_MoveToVehicle = 11,
            eState_Engaging = 12,
            eState_EngagingAdvance = 13,
            eState_EngagingRetreat = 14,
            eState_EngagingFromCover = 15,
            eState_EngagingCircle = 16,
            eState_IdleOccluded = 17,
            eState_IdleGuard = 18,
            eState_IdleInVehicle = 19,
            eState_React = 20,
            eState_ARCBTotal = 21
        };

        // RuffKing: cAgressiveResponseBasePrototype (0x90) plus eight tuning values; CD2's factory 0x824C9210
        // allocates 0xB0 and zeroes the six range floats.
        class cAgressiveResponseChaseBehaviourPrototype : public cAgressiveResponseBase::cAgressiveResponseBasePrototype
        {
        public:
            __forceinline cAgressiveResponseChaseBehaviourPrototype(const RWS::CAttributePacket &packet)
                : cAgressiveResponseBasePrototype(packet),
                  m_fMaxExitVehicleSpeedSq(0.0f), m_fOnFootMaxDesirableRangeSq(0.0f),
                  m_fOnFootMinDesirableRangeSq(0.0f), m_fOnFootMinSweetSpotRangeSq(0.0f),
                  m_fOnFootMaxSweetSpotRangeSq(0.0f), m_fOnFootRetreatRangeSq(0.0f)
            {
            }
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            float m_fMaxExitVehicleSpeedSq;         // 0x90
            float m_fOnFootMaxDesirableRangeSq;     // 0x94
            float m_fOnFootMinDesirableRangeSq;     // 0x98
            float m_fOnFootMinSweetSpotRangeSq;     // 0x9C
            float m_fOnFootMaxSweetSpotRangeSq;     // 0xA0
            float m_fOnFootRetreatRangeSq;          // 0xA4
            unsigned int m_nIdleOccludedTime;       // 0xA8
            unsigned int m_nIdleGuardTime;          // 0xAC

            CD2_LAYOUT_CHECKS(cAgressiveResponseChaseBehaviourPrototype,
                CD2_SIZE(cAgressiveResponseChaseBehaviourPrototype, 0xB0)
                CD2_OFFSET(cAgressiveResponseChaseBehaviourPrototype, m_fMaxExitVehicleSpeedSq, 0x90)
                CD2_OFFSET(cAgressiveResponseChaseBehaviourPrototype, m_nIdleGuardTime, 0xAC))
        };

        // CD2 spawning initializer 0x82F99518 names placement factory 0x824c92b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgressiveResponseChaseBehaviourClass;

        // Inlined into SpawnFromPrototype (0x824C92B0): the base constructor (0x824C9180) takes only this.
        __forceinline cAgressiveResponseChaseBehaviour(GOM::cObjectPrototype *pPrototype)
            : m_nUnknown100(0), m_nUnknown108(0), m_pVehicleToGetIn(0),
              m_fCurrentGoalDistanceSq(0.0f), m_fFailedToPathTime(-1.0f), m_fEnteredVehicleTime(-1.0f),
              m_bTransitioningToCover(false),
              m_pARCBProto(static_cast<cAgressiveResponseChaseBehaviourPrototype *>(pPrototype))
        {
        }
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        // Overrides of base slots (under the base stand-in's slot names).
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // OnCharacterEvent
        virtual void Slot97();
        virtual int GetTargetId();      // 116: RuffKing RetTargetingFlags
        virtual void V117();            // 117: RuffKing OnTargetLost

        // Own virtuals, slots 120..153 (RuffKing names and order).
        virtual void EnterGettingOut();                 // 120
        virtual void EnterMoveAdvance();                // 121
        virtual void EnterMoveRetreat();                // 122
        virtual void EnterMoveToCover();                // 123
        virtual void EnterMoveToVehicle();              // 124
        virtual void EnterEngaging();                   // 125
        virtual void EnterEngagingAdvance();            // 126
        virtual void EnterEngagingRetreat();            // 127
        virtual void EnterEngagingFromCover();          // 128
        virtual void EnterEngagingCircle();             // 129
        virtual void EnterIdleOccluded();               // 130
        virtual void EnterIdleGuard();                  // 131
        virtual void EnterIdleInVehicle();              // 132
        virtual void EnterReact();                      // 133
        virtual void OnUpdateMoveAdvance(float);        // 134
        virtual void OnUpdateMoveRetreat(float);        // 135
        virtual void OnUpdateMoveToCover(float);        // 136
        virtual void OnUpdateMoveToVehicle(float);      // 137
        virtual void OnUpdateEngaging(float);           // 138
        virtual void OnUpdateEngagingAdvance(float);    // 139
        virtual void OnUpdateEngagingRetreat(float);    // 140
        virtual void OnUpdateEngagingFromCover(float);  // 141
        virtual void OnUpdateEngagingCircle(float);     // 142
        virtual void OnUpdateIdleOccluded(float);       // 143
        virtual void OnUpdateIdleGuard(float);          // 144
        virtual void OnUpdateIdleInVehicle(float);      // 145
        virtual void OnUpdateReact(float);              // 146
        virtual void ExitGettingOut();                  // 147
        virtual void ExitMoveToCover();                 // 148
        virtual void ExitEngagingFromCover();           // 149
        virtual void ExitMoveRetreat();                 // 150
        virtual void OnFullbodyAnimFinishedOrInterrupted(); // 151
        virtual bool LookForCover();                    // 152
        virtual void StartReaction(NPCTarget *pInstigator, const cChaseBehaviour::Vec3 &vReactionPos, char nReaction,
                                   unsigned int nReactionFlags); // 153

        unsigned int m_nUnknown100;                     // 0x100
        unsigned int m_nUnknown104;                     // 0x104
        unsigned int m_nUnknown108;                     // 0x108
        cCoverPoint *m_pCoverPoint;                     // 0x10C
        Fun_Runtime::cSafeDeletablePointer<Vehicle::cVehicle> m_pVehicleToGetIn; // 0x110
        unsigned int m_nTargetVehicleSeat;              // 0x120
        float m_fCurrentGoalDistanceSq;                 // 0x124
        float m_fFailedToPathTime;                      // 0x128
        float m_fNextCoverCheckTime;                    // 0x12C
        float m_fEnteredVehicleTime;                    // 0x130
        bool m_bTransitioningToCover;                   // 0x134
        cAgressiveResponseChaseBehaviourPrototype *m_pARCBProto; // 0x138
        // CD2's class size is 0x140; the last field ends at 0x13C. The real NPCBehaviour base is 16-byte aligned
        // (a Vec3 member), which the flat NPCBehaviourSM stand-in is not, so no size check here yet.

        CD2_LAYOUT_CHECKS(cAgressiveResponseChaseBehaviour,
            CD2_OFFSET(cAgressiveResponseChaseBehaviour, m_pCoverPoint, 0x10C)
            CD2_OFFSET(cAgressiveResponseChaseBehaviour, m_pVehicleToGetIn, 0x110)
            CD2_OFFSET(cAgressiveResponseChaseBehaviour, m_fCurrentGoalDistanceSq, 0x124)
            CD2_OFFSET(cAgressiveResponseChaseBehaviour, m_bTransitioningToCover, 0x134)
            CD2_OFFSET(cAgressiveResponseChaseBehaviour, m_pARCBProto, 0x138))
    };
}

#endif
