// CD2 constructor 0x824BABB0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/FreakBase.h"
#include "gom/object_prototype.h"
#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class Scrounger : public AI::FreakBase
    {
    public:
        // CD2 factory 0x824BAA80 forwards only this, without a prototype argument.
        Scrounger();
        // CD2 spawning initializer 0x82F943C8 names placement factory 0x824baa80.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pScroungerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
