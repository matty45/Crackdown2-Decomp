// CD2 constructor 0x8236AA48 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#ifndef AI_CPILOTRESPAWN_H
#define AI_CPILOTRESPAWN_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cPilotRespawn : public AI::NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F9C270 names placement factory 0x824d4220.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPilotRespawnClass;

        cPilotRespawn();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8200A568 differs from NPCBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824D43E0
        virtual void OnExit(); // slot 69: 0x824D3590
        virtual void Slot71(); // slot 71: 0x824D4550
        virtual void Slot72(); // slot 72: 0x824A8CA0
        virtual void Slot79(); // slot 79: 0x824D4510
        virtual void Slot89(); // slot 89: 0x824D42A8
    };
}

#endif

