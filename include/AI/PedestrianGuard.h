// CD2 constructor 0x824AB1E0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/cNPCArmourySetup.h"
#include "AI/cPedestrianBase.h"
#include "gom/object_prototype.h"
#ifndef AI_PedestrianGuard_H
#define AI_PedestrianGuard_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class PedestrianGuard : public AI::cPedestrianBase, public cNPCArmourySetup
    {
    public:
        // CD2 placement factory forwards only this; later reference builds add a prototype argument.
        PedestrianGuard();
        // CD2 spawning initializer 0x82F92EA0 names placement factory 0x824ab0b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pPedestrianGuardClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
