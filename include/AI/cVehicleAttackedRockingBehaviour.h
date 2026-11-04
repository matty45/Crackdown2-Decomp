// AI::cVehicleAttackedRockingBehaviour (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824CF790) calls NPCBehaviour's constructor (0x824A89C8), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H
#define AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H

#include "AI/cChaseBehaviour.h"
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
        // CD2 MakeNew (0x824CF6C8) allocates 0xB0 bytes, calls AI::NPCBehaviourPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class cVehicleAttackedRockingBehaviourPrototype : public AI::NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cVehicleAttackedRockingBehaviourPrototype(const RWS::CAttributePacket &packet)
                : AI::NPCBehaviourPrototype(packet), m_fUnknown90(0.3f), m_fUnknown94(3.0f), m_fUnknown98(2.0f), m_fUnknown9C(1000.0f), m_fUnknownA0(5000.0f), m_fUnknownA4(4.0f) {}

        private:
            float m_fUnknown90; // 0x90
            float m_fUnknown94; // 0x94
            float m_fUnknown98; // 0x98
            float m_fUnknown9C; // 0x9C
            float m_fUnknownA0; // 0xA0
            float m_fUnknownA4; // 0xA4
            unsigned char m_padA8[0xB0 - 0xA8];

            CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviourPrototype,
                CD2_SIZE(cVehicleAttackedRockingBehaviourPrototype, 0xB0)
                CD2_OFFSET(cVehicleAttackedRockingBehaviourPrototype, m_fUnknown90, 0x90))
        };

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

