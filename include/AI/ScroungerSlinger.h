// AI::ScroungerSlinger (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824BE608) calls Scrounger's constructor (0x824BABB0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_SCROUNGERSLINGER_H
#define AI_SCROUNGERSLINGER_H

#include "AI/Scrounger.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class ScroungerSlinger : public Scrounger
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pScroungerSlingerClass;

    private:
        unsigned int m_nUnknown130; // 0x130
        unsigned int m_nUnknown134; // 0x134
        bool m_bUnknown138; // 0x138
        unsigned char m_pad139[0x140 - 0x139];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline ScroungerSlinger() : m_nUnknown130(0), m_nUnknown134(0), m_bUnknown138(false) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(ScroungerSlinger,
            CD2_SIZE(ScroungerSlinger, 0x140)
            CD2_OFFSET(ScroungerSlinger, m_nUnknown130, 0x130))
    };
}

#endif

