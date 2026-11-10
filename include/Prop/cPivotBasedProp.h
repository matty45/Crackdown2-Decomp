// Prop::cPivotBasedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8273AED8) is slot 11 of the vtable at 0x8213FEB8, as cNonGameBase's RetClassName.
#ifndef PROP_CPIVOTBASEDPROP_H
#define PROP_CPIVOTBASEDPROP_H

#include "Prop/cProp.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/cStateMachine.h"
#include "fun_runtime/State.h"

namespace Prop
{
    // CD2 constructor 0x8273AFF8: cProp, then the RuffKing cStateMachine base at 0xE30 (zeroed, no vptr). Primary
    // table 0x8213FEB8 has 345 slots: 341/342 the constraint-data hooks (both an empty blr), 343/344 RetSTATE_Base.
    class cPivotBasedProp : public Prop::cProp, public Fun_Runtime::cStateMachine
    {
    public:
        // CD2 0x823616B8: restores this class's vtables (primary 0x8213FEB8), then calls cProp's destructor.
        virtual ~cPivotBasedProp();
        // CD2 placement factory 0x8273AEE8; RuffKing signature.
        cPivotBasedProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing's prototype layout; CD2 factory 0x8273AE80 confirms size 0x520
        // and calls the out-of-line prototype constructor at 0x8273B208.
        class cPivotBasedPropPrototype : public cProp::cPropPrototype
        {
        public:
            cPivotBasedPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            Fun_Runtime::Vec3 m_vecPivot;
            Fun_Runtime::Vec3 m_vecHingeAxis;
            Fun_Runtime::Vec3 m_vecPerpAxis;

            CD2_LAYOUT_CHECKS(cPivotBasedPropPrototype,
                CD2_SIZE(cPivotBasedPropPrototype, 0x520)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecPivot, 0x4F0)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecHingeAxis, 0x500)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecPerpAxis, 0x510))
        };
        static const Fun_Runtime::cClass *ms_pcPivotBasedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        virtual void CreateConstraintData() {}      // slot 341
        virtual void DestroyConstraintData();       // slot 342
        // RuffKing state class; CD2 table 0x8213DFE0.
        class STATE_Base : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *pSM);
            virtual void EndState(Fun_Runtime::cStateMachine *pSM);
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
        };

    protected:
        static Fun_Runtime::State *StaticRetSTATE_Base();
        // Non-const first: MSVC reverses overload slots (cHingedProp's GoTo*/IsIn* calls show it).
        virtual Fun_Runtime::State *RetSTATE_Base();         // slots 343/344 (0x8273AFA8, folded)
        virtual Fun_Runtime::State *RetSTATE_Base() const;

    public:
        // CD2: cPivotBasedProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot27(); // 27: 0x8273B1A0
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8273B478
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8273B480
    public:
        // CD2: cPivotBasedProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void vf272(); // 272: 0x82686318
    public:
        CD2_LAYOUT_CHECKS(cPivotBasedProp,
            CD2_SIZE(cPivotBasedProp, 0xE40))
    };
}

#endif // PROP_CPIVOTBASEDPROP_H
