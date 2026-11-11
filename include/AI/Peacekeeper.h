// CD2 constructor 0x824C6C58 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/CellGuard.h"
#include "gom/object_prototype.h"
#ifndef AI_PEACEKEEPER_H
#define AI_PEACEKEEPER_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class Peacekeeper : public AI::CellGuard
    {
    public:
        // CD2 descriptor 0x823a0528 names this class; spawning registration 0x82F978A8.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        static const Fun_Runtime::cClass *ms_pPeacekeeperClass;

        Peacekeeper();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8210AEB0: overrides relative to CellGuard.
        virtual void OnEnter(); // slot 68: 0x824C6D28
        virtual void OnExit(); // slot 69: 0x82377328
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // slot 80: 0x824C74F0
        virtual void Slot81(); // slot 81: 0x824C7450
    };
}

#endif

