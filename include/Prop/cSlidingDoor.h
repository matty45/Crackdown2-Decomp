#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Prop::cSlidingDoor (Crackdown 2): STAND-IN for the class name only. Base Prop::cPrismaticProp, as in RuffKing's
// header; RetClassName (0x82746958) is slot 11 of the vtable at 0x82011C50, as cNonGameBase's RetClassName.
// RuffKing's second base AI::cPathObjectOwner: CD2's constructor (0x82746A78) builds it inline at 0xED0; the class
// has no fields of its own and ends at 0xF00, its registered size.
#ifndef PROP_CSLIDINGDOOR_H
#define PROP_CSLIDINGDOOR_H

#include "Prop/cPrismaticProp.h"
#include "AI/cPathObjectOwner.h"

namespace Prop
{
    class cSlidingDoor : public Prop::cPrismaticProp, public AI::cPathObjectOwner
    {
    public:
        // RuffKing signature; CD2's placement factory tail-calls 0x82746A78.
        cSlidingDoor(GOM::cObjectPrototype *);
        static const Fun_Runtime::cClass *ms_pcSlidingDoorClass;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 MakeNew (0x827468e8) allocates 0x530 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor (0x8273CBD0) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cSlidingDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cSlidingDoorPrototype(const RWS::CAttributePacket &packet) : Prop::cPrismaticProp::cPrismaticPropPrototype(packet) {}

            // CD2: cSlidingDoorPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8273CC70
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82746D80
        public:
            CD2_LAYOUT_CHECKS(cSlidingDoorPrototype, CD2_SIZE(cSlidingDoorPrototype, 0x530))
        };

        // CD2 0x82746988 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x82746878 / 0x82746888: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x82746B78 (out of line: cAgencyGarageDoor's destructor calls it).
        virtual ~cSlidingDoor();

        // The slots where CD2's table (0x82011C50) differs from cPrismaticProp's, with RuffKing's names: all are
        // RuffKing's cSlidingDoor overrides. Slot 0 holds the deleting destructor cTODSlidingDoor's object kept (0x82747258).
        virtual void TickUpdate(float dt); // 23: 0x8237CE68
        virtual bool IsAIEntityOwner(Kaim::CEntity *pEntity); // 61: 0x82746D38
        // cSafeDeletable slot 1: 0x82732D40 returns this class's script registrar (built by its initializer 0x82FFBD28);
        // the body lies in cAgencyGarageDoor's object.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // cPathObjectOwner's table at 0xED0 (0x82144970); 3 and 4 hold the shared "return 0" body.
        virtual bool CreatePathObject(); // 0: 0x82746C48
        virtual void DestroyPathObject(); // 1: 0x82746CC8
        virtual unsigned char GetCost(Kaim::CEntity *bot, Kaim::CEdge &edge, Kaim::CConstraint &constraint, float &cost); // 3
        virtual unsigned char CanGoFromTo(Kaim::CEntity &, const Kaim::CVector &, const Kaim::CVector &); // 4
        virtual void OnEnterGraph(AI::cStreamingGraph *pStreamingGraph); // 9: 0x82746D18
        virtual void OnExitGraph(AI::cStreamingGraph *pStreamingGraph); // 10: 0x82746D20

    protected:
        virtual void OnFinishedSlidingToMin(); // 349: 0x82746D60
        // RuffKing's states; CD2's tables 0x821449D4 and 0x821449E8 replace both physical-state callbacks.
        class STATE_Min : public cPrismaticProp::STATE_Min
        {
        public:
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Min();
        virtual Fun_Runtime::State *RetSTATE_Min();       // slots 351/352 (0x82381100)
        virtual Fun_Runtime::State *RetSTATE_Min() const;
        class STATE_Max : public cPrismaticProp::STATE_Max
        {
        public:
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
        };
        static Fun_Runtime::State *StaticRetSTATE_Max();
        virtual Fun_Runtime::State *RetSTATE_Max();       // slots 353/354 (0x82746A28)
        virtual Fun_Runtime::State *RetSTATE_Max() const;

        CD2_LAYOUT_CHECKS(cSlidingDoor,
            CD2_SIZE(cSlidingDoor, 0xF00))
    };
}

#endif // PROP_CSLIDINGDOOR_H
