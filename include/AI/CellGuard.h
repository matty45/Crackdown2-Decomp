// CD2 constructor 0x821F09C8 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/cNPCArmourySetup.h"
#include "AI/NPCArmedBehaviour.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#ifndef AI_CellGuard_H
#define AI_CellGuard_H

#include "rws/attributes.h"

namespace AI
{
    class CellGuard : public AI::NPCArmedBehaviour, public cNPCArmourySetup
    {
    public:
        // CD2 table 0x8210A8E0 extends the inherited interface at these slots.
        virtual void vf132();
        virtual void vf133();
        virtual void vf134();
        virtual void vf135();
        virtual void vf136();
        virtual void vf137();
        virtual void vf138();
        virtual void vf139();

        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x8381f1c0; its initializer names CellGuard.
        static const Fun_Runtime::cClass *ms_pCellGuardClass;
        // CD2 factory 0x824C0B70 forwards only this, without a prototype argument.
        CellGuard();
        // CD2 table 0x8210A8E0 overrides the armed base's seven pure state callbacks
        // with the shared empty body at 0x82580578; names come from RuffKing.
        virtual void OnIdle();
        virtual void OnInvestigating();
        virtual void OnPatrolling();
        virtual void OnAttacking();
        virtual void OnCover();
        virtual void OnAmbient();
        virtual void OnDrive();
        // CD2 descriptor 0x82250988 names this class; spawning registration 0x82F95B88.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8210A8E0: overrides relative to NPCArmedBehaviour.
        virtual void OnEnter(); // slot 68: 0x824C1880
        virtual void OnExit(); // slot 69: 0x824C1BF0
        virtual void Slot71(); // slot 71: 0x82250650
        virtual void Slot73(); // slot 73: 0x824C1F48
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824C1CC8
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824C2078
        virtual void Slot77(); // slot 77: 0x824C11C8
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // slot 80: 0x824C2700
        virtual void Slot81(); // slot 81: 0x824C3070
        virtual void Slot82(); // slot 82: 0x824C1FF8
        virtual void Slot83(); // slot 83: 0x824C2A50
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824C14C0
        virtual void Slot87(); // slot 87: 0x824C2D90
        virtual unsigned char GetStateReplicationInfo() const; // slot 89: 0x824C0EA0
        virtual void OnReplicatedEnter(unsigned char); // slot 97: 0x824C0EB8
    };
}

#endif
