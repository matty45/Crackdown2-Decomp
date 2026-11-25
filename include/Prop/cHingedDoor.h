#include "gom/object_prototype.h"
#ifndef Prop_cHingedDoor_H
#define Prop_cHingedDoor_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "Prop/cHingedProp.h"
#include "AI/cPathObjectOwner.h"

namespace Prop
{
    // RuffKing's bases; CD2's constructor (0x82744560) builds cPathObjectOwner inline at 0xEB0.
    class cHingedDoor : public cHingedProp, public AI::cPathObjectOwner
    {
    public:
        // CD2 0x82744380: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 spawning initializer 0x82FFAFA8 names placement factory 0x82744360.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82744560: the placement factory (0x82744360) calls it out of line with the prototype.
        cHingedDoor(GOM::cObjectPrototype *);
        static const Fun_Runtime::cClass *ms_pcHingedDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing base/name; CD2 MakeNew 0x827442E0 calls cHingedPropPrototype's
        // constructor and installs this derived prototype's vtable, with no new fields.
        class cHingedDoorPrototype : public cHingedProp::cHingedPropPrototype
        {
        public:
            cHingedDoorPrototype(const RWS::CAttributePacket &packet) : cHingedPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        public:
            CD2_LAYOUT_CHECKS(cHingedDoorPrototype,
                CD2_SIZE(cHingedDoorPrototype, 0x530))
        };
        virtual const char *RetClassName() const;
        // CD2 0x82744270 / 0x82744280: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // The slots where CD2's table (0x82011680) differs from cHingedProp's, with RuffKing's names: all are RuffKing's
        // cHingedDoor overrides. 61 (0x82744E50) lies in cHingedSpawnDoor's object, where the linker kept the copy.
        virtual ~cHingedDoor(); // 0: 0x82744660
        virtual void TickUpdate(float dt); // 23: 0x82744780
        virtual bool IsAIEntityOwner(Kaim::CEntity *pEntity); // 61: 0x82744E50
        // cPathObjectOwner's table at 0xEB0 (0x82143E2C). 1 and 10 hold the bodies cSlidingDoor's table holds; 3 and 4
        // the shared "return 0" body.
        virtual bool CreatePathObject(); // 0: 0x82744788
        virtual void DestroyPathObject(); // 1: 0x82746CC8
        virtual unsigned char GetCost(Kaim::CEntity *bot, Kaim::CEdge &edge, Kaim::CConstraint &constraint, float &cost); // 3
        virtual unsigned char CanGoFromTo(Kaim::CEntity &, const Kaim::CVector &, const Kaim::CVector &); // 4
        virtual void OnEnterGraph(AI::cStreamingGraph *pStreamingGraph); // 9: 0x82744808
        virtual void OnExitGraph(AI::cStreamingGraph *pStreamingGraph); // 10: 0x82746D20

    protected:
        // RuffKing's states; CD2's tables 0x82143E90 and 0x82143EA4 replace both physical-state callbacks.
        class STATE_Min : public cHingedProp::STATE_Min
        {
        public:
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *pSM);
        };
        static Fun_Runtime::State *StaticRetSTATE_Min();
        virtual Fun_Runtime::State *RetSTATE_Min();       // slots 347/348 (0x827444C0)
        virtual Fun_Runtime::State *RetSTATE_Min() const;
        class STATE_Max : public cHingedProp::STATE_Max
        {
        public:
            virtual void EnterPhysicalState(Fun_Runtime::cStateMachine *pSM);
            virtual void LeavePhysicalState(Fun_Runtime::cStateMachine *);
        };
        static Fun_Runtime::State *StaticRetSTATE_Max();
        virtual Fun_Runtime::State *RetSTATE_Max();       // slots 349/350 (0x82744510)
        virtual Fun_Runtime::State *RetSTATE_Max() const;

        CD2_LAYOUT_CHECKS(cHingedDoor,
            CD2_SIZE(cHingedDoor, 0xEE0))
    };
}

#endif
