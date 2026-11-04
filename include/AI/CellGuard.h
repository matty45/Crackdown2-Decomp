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
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x8381f1c0; its initializer names CellGuard.
        static const Fun_Runtime::cClass *ms_pcCellGuardClass;
        // CD2 factory 0x824C0B70 forwards only this, without a prototype argument.
        CellGuard();
        // CD2 descriptor 0x82250988 names this class; spawning registration 0x82F95B88.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
