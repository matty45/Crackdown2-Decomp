// AI::cVehicleAttackedRockingBehaviour (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824CF790) calls NPCBehaviour's constructor (0x824A89C8), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H
#define AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H

#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cVehicleAttackedRockingBehaviour : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleAttackedRockingBehaviourClass;

    private:
        unsigned int m_nUnknownC0; // 0xC0
        unsigned char m_padC4[0xD0 - 0xC4];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline cVehicleAttackedRockingBehaviour() : m_nUnknownC0(1) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviour,
            CD2_SIZE(cVehicleAttackedRockingBehaviour, 0xD0)
            CD2_OFFSET(cVehicleAttackedRockingBehaviour, m_nUnknownC0, 0xC0))
    };
}

#endif

