// CD2 constructor 0x824BABB0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/FreakBase.h"
#include "gom/object_prototype.h"
#ifndef AI_Scrounger_H
#define AI_Scrounger_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    // RuffKing: AI::ScroungerPrototype : FreakPrototype, 528 bytes. CD2's Scrounger::MakeNew (0x824BAA18) allocates
    // 0x210 and calls this constructor (0x824BC850), which calls FreakPrototype's (0x824B0B78).
    class ScroungerPrototype : public FreakPrototype
    {
    public:
        ScroungerPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelledB0[0x210 - 0xB0];

        CD2_LAYOUT_CHECKS(ScroungerPrototype,
            CD2_SIZE(ScroungerPrototype, 0x210))
    };

    class Scrounger : public AI::FreakBase
    {
    public:
        // CD2 factory 0x824BAA80 forwards only this, without a prototype argument. CD2 0x824BABB0, out of line:
        // FreakBase's constructor (0x824ABD60), the class vptrs, then the word at 0x120 = 13.
        Scrounger();
        // CD2 spawning initializer 0x82F943C8 names placement factory 0x824baa80.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pScroungerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknown120; // 0x120 (name ours; the constructor sets 13)
        // Other own fields not recovered; 0x130 is the size its registrar and descriptor give.
        unsigned char m_unmodelled124[0x130 - 0x124];

        CD2_LAYOUT_CHECKS(Scrounger,
            CD2_SIZE(Scrounger, 0x130)
            CD2_OFFSET(Scrounger, m_nUnknown120, 0x120))
    };
}

#endif
