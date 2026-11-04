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
    };
}

#endif

