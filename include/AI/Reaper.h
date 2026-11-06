#include "gom/object_prototype.h"
#ifndef AI_REAPER_H
#define AI_REAPER_H

#include "gom/non_game_base.h"
#include "AI/FreakBase.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class Reaper : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F93F90 names placement factory 0x824b26a8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pReaperClass;

        Reaper();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        // RuffKing: Reaper::ReaperPrototype : FreakPrototype, 880 bytes. CD2's MakeNew (0x824B2640) allocates 0x370 and
        // calls this constructor (0x824B80A8), which calls FreakPrototype's (0x824B0B78).
        class ReaperPrototype : public FreakPrototype
        {
        public:
            ReaperPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelledB0[0x370 - 0xB0];

            CD2_LAYOUT_CHECKS(ReaperPrototype,
                CD2_SIZE(ReaperPrototype, 0x370))
        };

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

