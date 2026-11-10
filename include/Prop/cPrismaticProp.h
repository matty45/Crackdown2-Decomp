// Prop::cPrismaticProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273B5A0) is slot 11 of the vtable at 0x821405E8, as cNonGameBase's RetClassName.
#ifndef PROP_CPRISMATICPROP_H
#define PROP_CPRISMATICPROP_H

#include "Prop/cPivotBasedProp.h"
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"

class hkPrismaticConstraintData;
class hkConstraintInstance;

namespace Prop
{
    class cPrismaticProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 placement factory 0x8273B5B0; constructor signature follows RuffKing.
        cPrismaticProp(GOM::cObjectPrototype *);
        // CD2 0x8273BC98: restores this class's vtables (primary 0x821405E8), then calls the base destructor.
        // Out of line: cLift's and cWeaponCabinetDoor's destructors call it.
        virtual ~cPrismaticProp();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing layout; CD2 factory 0x8273B548 allocates 0x530 and calls constructor 0x8273CBD0.
        class cPrismaticPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cPrismaticPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fMinLinearLimit;
            float m_fMaxLinearLimit;
            float m_fSlideSpeed;
            float m_fSlideGain;

            CD2_LAYOUT_CHECKS(cPrismaticPropPrototype,
                CD2_SIZE(cPrismaticPropPrototype, 0x530)
                CD2_OFFSET(cPrismaticPropPrototype, m_fMinLinearLimit, 0x520)
                CD2_OFFSET(cPrismaticPropPrototype, m_fMaxLinearLimit, 0x524)
                CD2_OFFSET(cPrismaticPropPrototype, m_fSlideSpeed, 0x528)
                CD2_OFFSET(cPrismaticPropPrototype, m_fSlideGain, 0x52C))
        };
        static const Fun_Runtime::cClass *ms_pcPrismaticPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

        // CD2 primary table 0x821405E8 has 376 slots: RuffKing's new virtuals in declaration order from slot 345
        // (non-const RetSTATE_* first: MSVC reverses overload slots, see cHingedProp.h).
    protected:
        virtual void CreateMotor(float fVelocity, float fGain);   // slot 345
        virtual void DestroyMotor();                              // slot 346
        virtual void CreateConstraint();                          // slot 347
        virtual void DestroyConstraint();                         // slot 348
        virtual void OnFinishedSlidingToMin();                    // slot 349
        // RuffKing fields; CD2's constructor (0x8273BA68) initializes them at these offsets.
        Fun_Runtime::Mtx m_InitialTransform;
        Fun_Runtime::Vec3 m_vecOriginalWorldPos;
        Fun_Runtime::Vec3 m_PivotInWorldSpace;
        Fun_Runtime::Vec3 m_vecWorldSlideAxis;
        Fun_Runtime::Vec3 m_vecWorldPerpAxis;
        float m_fSlideSpeed;
        hkPrismaticConstraintData *m_pConstraintData;
        hkConstraintInstance *m_pConstraint;
        virtual bool IsKeyframed();                               // slot 350
        class STATE_Min : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Min();
        virtual Fun_Runtime::State *RetSTATE_Min();   // slots 351/352
        virtual Fun_Runtime::State *RetSTATE_Min() const;
        class STATE_Max : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Max();
        virtual Fun_Runtime::State *RetSTATE_Max();   // slots 353/354
        virtual Fun_Runtime::State *RetSTATE_Max() const;
        class STATE_Sliding_To_Min : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void Process(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Sliding_To_Min();
        virtual Fun_Runtime::State *RetSTATE_Sliding_To_Min();   // slots 355/356
        virtual Fun_Runtime::State *RetSTATE_Sliding_To_Min() const;
        class STATE_Sliding_To_Max : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void Process(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Sliding_To_Max();
        virtual Fun_Runtime::State *RetSTATE_Sliding_To_Max();   // slots 357/358
        virtual Fun_Runtime::State *RetSTATE_Sliding_To_Max() const;
        class STATE_Sliding_Free : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Sliding_Free();
        virtual Fun_Runtime::State *RetSTATE_Sliding_Free();   // slots 359/360
        virtual Fun_Runtime::State *RetSTATE_Sliding_Free() const;
        class STATE_Broken_Off : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Broken_Off();
        virtual Fun_Runtime::State *RetSTATE_Broken_Off();   // slots 361/362
        virtual Fun_Runtime::State *RetSTATE_Broken_Off() const;
        virtual void GoToInitialState();                          // slot 363
        // Slots 364..369.
        virtual void GoToMinState() { GoTo_State(RetSTATE_Min()); }
        virtual void GoToMaxState() { GoTo_State(RetSTATE_Max()); }
        virtual void GoToSlidingToMinState() { GoTo_State(RetSTATE_Sliding_To_Min()); }
        virtual void GoToSlidingToMaxState() { GoTo_State(RetSTATE_Sliding_To_Max()); }
        virtual void GoToSlidingFreeState() { GoTo_State(RetSTATE_Sliding_Free()); }
        virtual void GoToBrokenOffState() { GoTo_State(RetSTATE_Broken_Off()); }

    public:
        // Slots 370..375.
        virtual bool IsInMinState() { return IsIn_State(RetSTATE_Min()); }
        virtual bool IsInMaxState() { return IsIn_State(RetSTATE_Max()); }
        virtual bool IsInSlidingToMinState() { return IsIn_State(RetSTATE_Sliding_To_Min()); }
        virtual bool IsInSlidingToMaxState() { return IsIn_State(RetSTATE_Sliding_To_Max()); }
        virtual bool IsInSlidingFreeState() { return IsIn_State(RetSTATE_Sliding_Free()); }
        virtual bool IsInBrokenOffState() { return IsIn_State(RetSTATE_Broken_Off()); }

        CD2_LAYOUT_CHECKS(cPrismaticProp,
            CD2_SIZE(cPrismaticProp, 0xED0)
            CD2_OFFSET(cPrismaticProp, m_InitialTransform, 0xE40)
            CD2_OFFSET(cPrismaticProp, m_vecOriginalWorldPos, 0xE80)
            CD2_OFFSET(cPrismaticProp, m_vecWorldPerpAxis, 0xEB0)
            CD2_OFFSET(cPrismaticProp, m_fSlideSpeed, 0xEC0)
            CD2_OFFSET(cPrismaticProp, m_pConstraint, 0xEC8))
    };
}

#endif // PROP_CPRISMATICPROP_H
