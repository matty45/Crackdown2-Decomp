// Prop::cHingedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x82736E40) is slot 11 of the vtable at 0x8213E830, as cNonGameBase's RetClassName.
#ifndef PROP_CHINGEDPROP_H
#define PROP_CHINGEDPROP_H

#include "Prop/cPivotBasedProp.h"
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"

class hkPositionConstraintMotor;
class hkPoweredHingeConstraintData;
class hkConstraintInstance;

namespace Prop
{
    class cHingedProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 0x82736E70: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 placement factory 0x82736E50; RuffKing signature.
        cHingedProp(GOM::cObjectPrototype *);
        // CD2 0x82737698: restores this class's vtables (primary 0x8213E830), then calls the base destructor.
        // Out of line: cSpawnPortal's destructor calls it.
        virtual ~cHingedProp();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing fields; CD2's factory allocates 0x530 and invokes the constructor
        // at 0x82738740, also called by cHingedDoor's prototype factory.
        class cHingedPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cHingedPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fMinAngle;
            float m_fMaxAngle;
            bool m_RotFreeAtStart;
            bool m_bFlipHinge;

            CD2_LAYOUT_CHECKS(cHingedPropPrototype,
                CD2_SIZE(cHingedPropPrototype, 0x530)
                CD2_OFFSET(cHingedPropPrototype, m_fMinAngle, 0x520)
                CD2_OFFSET(cHingedPropPrototype, m_fMaxAngle, 0x524)
                CD2_OFFSET(cHingedPropPrototype, m_RotFreeAtStart, 0x528)
                CD2_OFFSET(cHingedPropPrototype, m_bFlipHinge, 0x529))
        };
        static const Fun_Runtime::cClass *ms_pcHingedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

        // CD2 primary table 0x8213E830 has 372 slots: RuffKing's new virtuals in declaration order from slot 345. MSVC
        // gives overloads reverse slots: GoToMinState calls slot 348, so the non-const RetSTATE_* comes first here.
    protected:
        virtual void CreateConstraint(bool bMotorActive, float fTargetAngle);   // slot 345
        virtual void DestroyConstraint();                                       // slot 346
        // RuffKing fields; CD2's constructor (0x827374E0) initializes them at these offsets.
        Fun_Runtime::Mtx m_InitialTransform;
        Fun_Runtime::Vec3 m_PivotInWorldSpace;
        bool m_RotFreeAtStart;
        hkPositionConstraintMotor *m_pMotor;
        hkPoweredHingeConstraintData *m_pConstraintData;
        hkConstraintInstance *m_pConstraint;
        bool m_bDoDingDong;
        class STATE_Min : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Min();
        virtual Fun_Runtime::State *RetSTATE_Min();                       // slots 347/348 (0x82737300)
        virtual Fun_Runtime::State *RetSTATE_Min() const;
        class STATE_Max : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Max();
        virtual Fun_Runtime::State *RetSTATE_Max();                       // slots 349/350 (0x82737350)
        virtual Fun_Runtime::State *RetSTATE_Max() const;
        class STATE_Rotating_To_Min : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void Process(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Rotating_To_Min();
        virtual Fun_Runtime::State *RetSTATE_Rotating_To_Min();           // slots 351/352 (0x827373A0)
        virtual Fun_Runtime::State *RetSTATE_Rotating_To_Min() const;
        class STATE_Rotating_To_Max : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Rotating_To_Max();
        virtual Fun_Runtime::State *RetSTATE_Rotating_To_Max();           // slots 353/354 (0x827373F0)
        virtual Fun_Runtime::State *RetSTATE_Rotating_To_Max() const;
        class STATE_Rotating_Free : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
        };
        static Fun_Runtime::State *StaticRetSTATE_Rotating_Free();
        virtual Fun_Runtime::State *RetSTATE_Rotating_Free();             // slots 355/356 (0x82737440)
        virtual Fun_Runtime::State *RetSTATE_Rotating_Free() const;
        class STATE_Broken_Off : public Prop::cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Broken_Off();
        virtual Fun_Runtime::State *RetSTATE_Broken_Off();                // slots 357/358 (0x82737490)
        virtual Fun_Runtime::State *RetSTATE_Broken_Off() const;
        virtual void GoToInitialState();                                        // slot 359
        // Slots 360..365; CD2 0x82736E80, 0x82736EC8 and 0x82736F10 are three of them, the others folded elsewhere.
        virtual void GoToMinState() { GoTo_State(RetSTATE_Min()); }
        virtual void GoToMaxState() { GoTo_State(RetSTATE_Max()); }
        virtual void GoToRotatingToMinState() { GoTo_State(RetSTATE_Rotating_To_Min()); }
        virtual void GoToRotatingToMaxState() { GoTo_State(RetSTATE_Rotating_To_Max()); }
        virtual void GoToRotatingFreeState() { GoTo_State(RetSTATE_Rotating_Free()); }
        virtual void GoToBrokenOffState() { GoTo_State(RetSTATE_Broken_Off()); }

    public:
        // Slots 366..371; CD2 0x82736F58, 0x82736FA0 and 0x82736FE8 are 368..370.
        virtual bool IsInMinState() { return IsIn_State(RetSTATE_Min()); }
        virtual bool IsInMaxState() { return IsIn_State(RetSTATE_Max()); }
        virtual bool IsInRotatingToMinState() { return IsIn_State(RetSTATE_Rotating_To_Min()); }
        virtual bool IsInRotatingToMaxState() { return IsIn_State(RetSTATE_Rotating_To_Max()); }
        virtual bool IsInRotatingFreeState() { return IsIn_State(RetSTATE_Rotating_Free()); }
        virtual bool IsInBrokenOffState() { return IsIn_State(RetSTATE_Broken_Off()); }

        CD2_LAYOUT_CHECKS(cHingedProp,
            CD2_SIZE(cHingedProp, 0xEB0)
            CD2_OFFSET(cHingedProp, m_InitialTransform, 0xE40)
            CD2_OFFSET(cHingedProp, m_PivotInWorldSpace, 0xE80)
            CD2_OFFSET(cHingedProp, m_RotFreeAtStart, 0xE90)
            CD2_OFFSET(cHingedProp, m_pMotor, 0xE94)
            CD2_OFFSET(cHingedProp, m_pConstraint, 0xE9C)
            CD2_OFFSET(cHingedProp, m_bDoDingDong, 0xEA0))
    };
}

#endif // PROP_CHINGEDPROP_H
