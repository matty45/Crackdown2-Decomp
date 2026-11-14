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

        // CD2: ScroungerSlinger's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void OnEnterReplicatedState(unsigned char); // 72: 0x824BE830
        virtual void Slot73(); // 73: 0x82580578
        virtual void OnEvent74(AI::NPCTarget *); // 74: 0x824BEF78
        virtual void OnEvent75(AI::NPCTarget *); // 75: 0x824BEF90
        virtual void Slot77(); // 77: 0x824BF038
        virtual void Slot80(unsigned char,unsigned char,unsigned char); // 80: 0x824BF5A8
        virtual void Slot82(); // 82: 0x824BEFC0
        virtual unsigned char GetStateReplicationInfo() const; // 89: 0x824BE8C0
        virtual void GetState(int); // 100: 0x824BE908
        virtual void Slot101(); // 101: 0x824BE7C0
        virtual void V102(); // 102: 0x824BE808
    private:
        CD2_LAYOUT_CHECKS(ScroungerSlinger,
            CD2_SIZE(ScroungerSlinger, 0x140)
            CD2_OFFSET(ScroungerSlinger, m_nNextSlingTime, 0x130)
            CD2_OFFSET(ScroungerSlinger, m_bSniper, 0x138))

    public:
        // CD2 table 0x8210A398 differs from Scrounger at these inherited slots.
        virtual void vf120(); // slot 120: 0x824BEEA0
        virtual void vf157(); // slot 157: 0x824BF7D8
        virtual void vf162(); // slot 162: 0x824BF768
        virtual void vf165(); // slot 165: 0x824BEF28
    };
}

#endif

