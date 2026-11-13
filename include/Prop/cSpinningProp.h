// Prop::cSpinningProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273E670) is slot 11 of the vtable at 0x82141860, as cNonGameBase's RetClassName.
#ifndef PROP_CSPINNINGPROP_H
#define PROP_CSPINNINGPROP_H

#include "Prop/cPivotBasedProp.h"

class hkHingeConstraintData;
class hkMotorAction;
class hkConstraintInstance;

namespace Prop
{
    class cSpinningProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 registrar 0x8273E738 registers these nonvirtual actions; signatures
        // follow the reference header and their direct member-pointer targets.
        void SpinClockWise();
        void SpinAntiClockWise();
        void SpinFree();
    protected:
        // CD2 table 0x82141860 extends cPivotBasedProp's 345 slots. Reference
        // names/order plus the script thunks establish the four queries at 363..366.
        virtual void CreateMotor(float); // 345
        virtual void DestroyMotor(); // 346
        virtual void CreateConstraint(); // 347
        virtual void DestroyConstraint(); // 348
        class STATE_Spinning_ClockWise : public cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Spinning_ClockWise, CD2_SIZE(STATE_Spinning_ClockWise, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Spinning_ClockWise();
        virtual Fun_Runtime::State *RetSTATE_Spinning_ClockWise(); // 349/350
        virtual Fun_Runtime::State *RetSTATE_Spinning_ClockWise() const;
        class STATE_Spinning_AntiClockWise : public cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Spinning_AntiClockWise, CD2_SIZE(STATE_Spinning_AntiClockWise, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Spinning_AntiClockWise();
        virtual Fun_Runtime::State *RetSTATE_Spinning_AntiClockWise(); // 351/352
        virtual Fun_Runtime::State *RetSTATE_Spinning_AntiClockWise() const;
        class STATE_Spinning_Free : public cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Spinning_Free, CD2_SIZE(STATE_Spinning_Free, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Spinning_Free();
        virtual Fun_Runtime::State *RetSTATE_Spinning_Free(); // 353/354
        virtual Fun_Runtime::State *RetSTATE_Spinning_Free() const;
        class STATE_Broken_Off : public cPivotBasedProp::STATE_Base
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Broken_Off, CD2_SIZE(STATE_Broken_Off, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Broken_Off();
        virtual Fun_Runtime::State *RetSTATE_Broken_Off(); // 355/356
        virtual Fun_Runtime::State *RetSTATE_Broken_Off() const;
        virtual bool CanGoToInitialState() const; // 357
        // CD2 0x8273EC48: the prototype's motion type picks the broken-off or clockwise state.
        virtual void GoToInitialState(); // 358
        virtual void GoToSpinningClockWiseState() { GoTo_State(RetSTATE_Spinning_ClockWise()); } // 359
        virtual void GoToSpinningAntiClockWiseState() { GoTo_State(RetSTATE_Spinning_AntiClockWise()); } // 360
        virtual void GoToSpinningFreeState() { GoTo_State(RetSTATE_Spinning_Free()); } // 361
        virtual void GoToBrokenOffState() { GoTo_State(RetSTATE_Broken_Off()); } // 362
    public:
        virtual bool IsInSpinningClockWiseState() { return IsIn_State(RetSTATE_Spinning_ClockWise()); } // 363, thunk 0x8273FA08
        virtual bool IsInSpinningAntiClockWiseState() { return IsIn_State(RetSTATE_Spinning_AntiClockWise()); } // 364, thunk 0x8273FA40
        virtual bool IsInSpinningFreeState() { return IsIn_State(RetSTATE_Spinning_Free()); } // 365, thunk 0x8273FA58
        virtual bool IsInBrokenOffState() { return IsIn_State(RetSTATE_Broken_Off()); } // 366, shared thunk 0x82738E08
        // CD2 0x8273EB20: restores this class's vtables, then calls cPivotBasedProp's destructor.
        virtual ~cSpinningProp();
        // CD2 placement factory 0x8273E680; constructor signature follows RuffKing.
        cSpinningProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing layout; CD2 factory 0x8273E618 allocates 0x530 and calls constructor 0x8273F5C0.
        class cSpinningPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cSpinningPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fSpinSpeed;
            float m_fSpinAccel;

            CD2_LAYOUT_CHECKS(cSpinningPropPrototype,
                CD2_SIZE(cSpinningPropPrototype, 0x530)
                CD2_OFFSET(cSpinningPropPrototype, m_fSpinSpeed, 0x520)
                CD2_OFFSET(cSpinningPropPrototype, m_fSpinAccel, 0x524))
        };
        static const Fun_Runtime::cClass *ms_pcSpinningPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2: cSpinningProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8273EE70
        virtual void Slot13(); // 13: 0x8273EDE0
        virtual void EnterGhostState(); // 271: 0x8273EED8
        virtual void vf283(); // 283: 0x8273EF58
        virtual void Breakoff(bool bForce); // 314: 0x8273EEC8
        virtual void OnSpawnedAsFragment(cGameBase *pParent); // 317: 0x8273EF18
        virtual void vf320(); // 320: 0x827E56A8
        virtual void CreateConstraintData(); // 341: 0x8273F000
        virtual void DestroyConstraintData(); // 342: 0x8273F250
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8273FA38
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8273FA50
    protected:
        // RuffKing's members at CD2's offsets (cPivotBasedProp ends at 0xE40; the registrar gives size 0xE50):
        // DestroyConstraintData (0x8273F250) releases and clears the first.
        hkHingeConstraintData *m_pConstraintData;       // 0xE40
        hkMotorAction *m_pMotorAction;                  // 0xE44
        hkConstraintInstance *m_pConstraint;            // 0xE48
    private:
        CD2_LAYOUT_CHECKS(cSpinningProp,
            CD2_SIZE(cSpinningProp, 0xE50)
            CD2_OFFSET(cSpinningProp, m_pConstraintData, 0xE40))
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x82457AD8

    public:
        // CD2 table 0x82141860 differs from cPivotBasedProp at these inherited slots.
        // CD2 0x8273EBD8: cProp's Init, then the initial state when allowed.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // slot 18: 0x8273EBD8
    };
}

#endif // PROP_CSPINNINGPROP_H
