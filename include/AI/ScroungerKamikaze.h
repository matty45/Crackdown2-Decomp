// AI::ScroungerKamikaze (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824BDDF0) calls Scrounger's constructor (0x824BABB0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_SCROUNGERKAMIKAZE_H
#define AI_SCROUNGERKAMIKAZE_H

#include "AI/Scrounger.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class ScroungerKamikaze : public Scrounger
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pScroungerKamikazeClass;

    private:
        unsigned char m_pad130[0x140 - 0x130];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline ScroungerKamikaze() {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(ScroungerKamikaze,
            CD2_SIZE(ScroungerKamikaze, 0x140))
    };
}

#endif

