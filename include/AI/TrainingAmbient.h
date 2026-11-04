// AI::TrainingAmbient (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824C7C60) calls NPCBehaviour's constructor (0x824A89C8), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_TRAININGAMBIENT_H
#define AI_TRAININGAMBIENT_H

#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class TrainingAmbient : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pTrainingAmbientClass;

    private:
        unsigned int m_nUnknownC0; // 0xC0
        unsigned int m_nUnknownC4; // 0xC4
        unsigned char m_padC8[0xD0 - 0xC8];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline TrainingAmbient() : m_nUnknownC0(0), m_nUnknownC4(0) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(TrainingAmbient,
            CD2_SIZE(TrainingAmbient, 0xD0)
            CD2_OFFSET(TrainingAmbient, m_nUnknownC0, 0xC0))
    };
}

#endif

