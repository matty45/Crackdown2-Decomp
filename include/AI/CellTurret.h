#include "gom/object_prototype.h"
#ifndef AI_CELLTURRET_H
#define AI_CELLTURRET_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCArmedBehaviour.h"

namespace AI
{
    class CellTurret : public NPCArmedBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F96830 names placement factory 0x824c5250.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellTurretClass;

        CellTurret();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: CellTurret's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824C5DF8

    public:
        // CD2 table 0x8210ABE0 differs from NPCArmedBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824C55F0
        virtual void OnExit(); // slot 69: 0x824C5648
        virtual void Slot71(); // slot 71: 0x824C5C28
        virtual void Slot73(); // slot 73: 0x824C56B8
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824C56B8
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824C5798
        virtual void Slot79(); // slot 79: 0x824C34C0
        virtual void OnReplicatedEnter(unsigned char); // slot 97: 0x824C5420
        virtual void OnIdle(); // slot 102: 0x824C58B0
        virtual void OnInvestigating(); // slot 103: 0x824C5A58
        virtual void OnPatrolling(); // slot 104: 0x82580578
        virtual void OnAttacking(); // slot 105: 0x824C5B30
        virtual void OnCover(); // slot 106: 0x82580578
        virtual void OnAmbient(); // slot 109: 0x82580578
        virtual void OnDrive(); // slot 110: 0x82580578
        virtual void EnterSubStateInvestigating(); // slot 112: 0x824C54B8
    };
}

#endif

