// AI::cPedestrianBase (Crackdown 2): STAND-IN; RuffKing names and types. Evidence:
//   - Base AI::NPCBehaviour (RuffKing): the constructor (0x824A91F8) first calls NPCBehaviour's (0x824A89C8). Size 0x120
//     (its registrar). RuffKing's fields start at 0x100 where CD2's start at 0xC0.
//   - The constructor initialises, in declaration order: m_nState 0 and m_nReactFinState 2 (0xC0, 0xC1); the safe
//     pointers m_pObjToHold (0xC4) and m_pVehicle (0xD4; RuffKing's constructor installs a
//     cSafeDeletablePointer<VEHICLE_CONTROL::cVehicleController>, its header lists a raw pointer); three words at
//     0xE4..0xEC that RuffKing does not have (zeroed; names ours; three scalars, as an array schedules differently);
//     m_vReactionPoint and m_vVelocity (0xF0, 0x100) from Fun_Runtime::ZeroVec (an OldVec3 in CD2: x, y, z, w = 1.0);
//     m_nInitialEdge -1, m_nStoredCollisionFilterInfo 0, m_fCurrentTimer 8.0 (RuffKing loads m_fReactTimer there),
//     m_bPanicRun false, m_bAmbEventHasObject false, m_bDoReactions true.
//   - SpawnFromPrototype (0x824A90C8) placement-constructs it without a prototype argument.
#ifndef AI_CPEDESTRIANBASE_H
#define AI_CPEDESTRIANBASE_H

#include "AI/NPCBehaviour.h"
#include "fun_runtime/class.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"

namespace Prop { class cProp; }
namespace VEHICLE_CONTROL { class cVehicleController; }

namespace AI
{
    class cPedestrianBase : public NPCBehaviour
    {
    public:
        // CD2 table 0x8200B1F8 has 111 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf96(); // primary slot 96
        virtual void vf97(); // primary slot 97
        virtual void vf98(); // primary slot 98
        virtual void vf99(); // primary slot 99
        virtual void vf100(); // primary slot 100
        virtual void vf101(); // primary slot 101
        virtual void vf102(); // primary slot 102
        virtual void vf103(); // primary slot 103
        virtual void vf104(); // primary slot 104
        virtual void vf105(); // primary slot 105
        virtual void vf106(); // primary slot 106
        virtual void vf107(); // primary slot 107
        virtual void vf108(); // primary slot 108
        virtual void vf109(); // primary slot 109
        virtual void vf110(); // primary slot 110

        // CD2 0x824A9150 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        enum eState
        {
            eNull = 0,
            eWandering,
            eFleeing,
            eFleeingToCar,
            eFleeingDriving,
            eTrafficDriving,
            eAmbient,
            ePatrol,
            eSituationalReacting,
            eNumStates
        };

    protected:
        char m_nState;                                                                       // 0xC0
        char m_nReactFinState;                                                               // 0xC1
    private:
        Fun_Runtime::cSafeDeletablePointer<Prop::cProp> m_pObjToHold;                        // 0xC4
        Fun_Runtime::cSafeDeletablePointer<VEHICLE_CONTROL::cVehicleController> m_pVehicle; // 0xD4
        unsigned int m_nUnknownE4;                                                           // 0xE4
        unsigned int m_nUnknownE8;                                                           // 0xE8
        unsigned int m_nUnknownEC;                                                           // 0xEC
        Fun_Runtime::Vec3 m_vReactionPoint;                                                  // 0xF0
        Fun_Runtime::Vec3 m_vVelocity;                                                       // 0x100
        unsigned int m_nInitialEdge;                                                         // 0x110
        unsigned int m_nStoredCollisionFilterInfo;                                           // 0x114
        float m_fCurrentTimer;                                                               // 0x118
        bool m_bPanicRun;                                                                    // 0x11C
        bool m_bAmbEventHasObject;                                                           // 0x11D
        bool m_bDoReactions;                                                                 // 0x11E
        static const float m_fReactTimer;

    public:
        cPedestrianBase();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcPedestrianBaseClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        // CD2: cPedestrianBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x824A9310
        virtual void Slot2(); // cSafeDeletable 2: 0x824AA9D8
    public:
        CD2_LAYOUT_CHECKS(cPedestrianBase,
            CD2_SIZE(cPedestrianBase, 0x120)
            CD2_OFFSET(cPedestrianBase, m_nState, 0xC0)
            CD2_OFFSET(cPedestrianBase, m_pObjToHold, 0xC4)
            CD2_OFFSET(cPedestrianBase, m_pVehicle, 0xD4)
            CD2_OFFSET(cPedestrianBase, m_nUnknownE4, 0xE4)
            CD2_OFFSET(cPedestrianBase, m_vReactionPoint, 0xF0)
            CD2_OFFSET(cPedestrianBase, m_vVelocity, 0x100)
            CD2_OFFSET(cPedestrianBase, m_nInitialEdge, 0x110)
            CD2_OFFSET(cPedestrianBase, m_fCurrentTimer, 0x118)
            CD2_OFFSET(cPedestrianBase, m_bDoReactions, 0x11E))

    public:
        // CD2 table 0x8200B1F8 differs from NPCBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824A9350
        virtual void OnExit(); // slot 69: 0x824A9588
        virtual void Slot71(); // slot 71: 0x824A9E18
        virtual void Slot72(); // slot 72: 0x824A8CA0
        virtual void Slot73(); // slot 73: 0x824A9888
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824A9728
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824A98F0
        virtual void Slot77(); // slot 77: 0x824A99F8
        virtual void Slot79(); // slot 79: 0x824A96C8
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // slot 80: 0x824AABA0
        virtual void Slot82(); // slot 82: 0x824A9B98
        virtual void Slot83(); // slot 83: 0x824AABF8
        virtual void Slot84(); // slot 84: 0x824A96B0
        virtual void Slot88(); // slot 88: 0x82370840
        virtual void Slot89(); // slot 89: 0x824D42A8
    };
}

#endif
