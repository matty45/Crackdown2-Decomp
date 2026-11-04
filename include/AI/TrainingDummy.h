// AI::TrainingDummy (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824C82D8) calls NPCBehaviour's constructor (0x824A89C8), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_TRAININGDUMMY_H
#define AI_TRAININGDUMMY_H

#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class TrainingDummy : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingDummyClass;

    private:
        unsigned int m_nUnknownC0; // 0xC0
        unsigned int m_nUnknownC4; // 0xC4
        bool m_bUnknownC8; // 0xC8
        bool m_bUnknownC9; // 0xC9
        unsigned char m_padCA[0xD0 - 0xCA];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline TrainingDummy() : m_nUnknownC0(0), m_nUnknownC4(0), m_bUnknownC8(false), m_bUnknownC9(false) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(TrainingDummy,
            CD2_SIZE(TrainingDummy, 0xD0)
            CD2_OFFSET(TrainingDummy, m_nUnknownC0, 0xC0))
    };
}

#endif

