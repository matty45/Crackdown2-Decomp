#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "gom/game_base.h"
// unknown::cPrismaticTrigger (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273D510) builds cClass(0xCB57, "cPrismaticTrigger", 0x160); 0x160 is the size its registrar gives.
#ifndef UNKNOWN_CPRISMATICTRIGGER_H
#define UNKNOWN_CPRISMATICTRIGGER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cPrismaticTrigger
    {
    public:
        // Prototype name ours. CD2's MakeNew (0x8273D3B0) allocates 0xF0, calls cGameBasePrototype's constructor
        // (0x82652850), stores this class's vptrs and zero at 0xE0: the constructor is inline. The word's name is ours.
        class cPrismaticTriggerPrototype : public cGameBase::cGameBasePrototype
        {
        public:
            __forceinline cPrismaticTriggerPrototype(const RWS::CAttributePacket &packet)
                : cGameBase::cGameBasePrototype(packet), m_nE0(0) {}

            unsigned int m_nE0;

            CD2_LAYOUT_CHECKS(cPrismaticTriggerPrototype,
                CD2_SIZE(cPrismaticTriggerPrototype, 0xF0)
                CD2_OFFSET(cPrismaticTriggerPrototype, m_nE0, 0xE0))
        };

        // CD2 0x8273D340: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8273D428: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF8890 names placement factory 0x8273d438.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPrismaticTriggerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CPRISMATICTRIGGER_H
