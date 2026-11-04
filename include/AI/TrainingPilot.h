// AI::TrainingPilot (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824C8DA8) calls NPCBehaviour's constructor (0x824A89C8), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_TRAININGPILOT_H
#define AI_TRAININGPILOT_H

#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class TrainingPilot : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingPilotClass;

    private:
        bool m_bUnknownC0; // 0xC0
        unsigned char m_padC1[0xD0 - 0xC1];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline TrainingPilot() : m_bUnknownC0(false) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(TrainingPilot,
            CD2_SIZE(TrainingPilot, 0xD0)
            CD2_OFFSET(TrainingPilot, m_bUnknownC0, 0xC0))
    };
}

#endif

