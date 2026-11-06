#include "gom/object_prototype.h"
#ifndef AI_SCROUNGERSLINGER_H
#define AI_SCROUNGERSLINGER_H

#include "gom/non_game_base.h"
#include "AI/Scrounger.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // RuffKing: AI::ScroungerSlingerPrototype : ScroungerPrototype, 688 bytes. CD2's ScroungerSlinger::MakeNew
    // (0x824BE5A0) allocates 0x2B0 and calls this constructor (0x824BF860), which calls ScroungerPrototype's
    // (0x824BC850).
    class ScroungerSlingerPrototype : public ScroungerPrototype
    {
    public:
        ScroungerSlingerPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled210[0x2B0 - 0x210];

        CD2_LAYOUT_CHECKS(ScroungerSlingerPrototype,
            CD2_SIZE(ScroungerSlingerPrototype, 0x2B0))
    };

    // Base Scrounger (CD2's inheritance registrar). The placement factory (0x824BE608) inlines this class's constructor
    // over Scrounger's (0x824BABB0) and clears the three fields below; names and order are RuffKing's.
    class ScroungerSlinger : public AI::Scrounger
    {
    public:
        // CD2 spawning initializer 0x82F94C38 names placement factory 0x824be608.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pScroungerSlingerClass;

        __forceinline ScroungerSlinger() : m_nNextSlingTime(0), m_nSlingTimeout(0), m_bSniper(false) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nNextSlingTime;              // 0x130
        unsigned int m_nSlingTimeout;               // 0x134
        bool m_bSniper;                             // 0x138
        unsigned char m_unmodelled139[0x140 - 0x139];

        CD2_LAYOUT_CHECKS(ScroungerSlinger,
            CD2_SIZE(ScroungerSlinger, 0x140)
            CD2_OFFSET(ScroungerSlinger, m_nNextSlingTime, 0x130)
            CD2_OFFSET(ScroungerSlinger, m_bSniper, 0x138))
    };
}

#endif

