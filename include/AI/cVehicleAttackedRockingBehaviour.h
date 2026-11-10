#include "gom/object_prototype.h"
#ifndef AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H
#define AI_CVEHICLEATTACKEDROCKINGBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCBehaviour.h"
#include "AI/cChaseBehaviour.h"
#include "cd2/layout.h"

namespace AI
{
    class cVehicleAttackedRockingBehaviour : public NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F9A5F8 names placement factory 0x824cf790.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleAttackedRockingBehaviourClass;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824CF790), which calls
        // NPCBehaviour's constructor (0x824A89C8) out of line and then sets the field below (name ours).
        __forceinline cVehicleAttackedRockingBehaviour() : m_nUnknownC0(1) {}

        // CD2's MakeNew (0x824CF6C8) allocates 0xB0, calls NPCBehaviourPrototype's constructor (0x824A8608) with the
        // packet, stores this prototype's vptrs (at 0 and 0x18) and the six float defaults below (names ours).
        class cVehicleAttackedRockingBehaviourPrototype : public NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew.
            __forceinline cVehicleAttackedRockingBehaviourPrototype(const RWS::CAttributePacket &packet)
                : NPCBehaviourPrototype(packet), m_fUnknown90(0.3f), m_fUnknown94(3.0f), m_fUnknown98(2.0f),
                  m_fUnknown9C(1000.0f), m_fUnknownA0(5000.0f), m_fUnknownA4(4.0f) {}

        private:
            float m_fUnknown90; // 0x90
            float m_fUnknown94; // 0x94
            float m_fUnknown98; // 0x98
            float m_fUnknown9C; // 0x9C
            float m_fUnknownA0; // 0xA0
            float m_fUnknownA4; // 0xA4
            unsigned char m_unmodelledA8[0xB0 - 0xA8];

            // CD2: cVehicleAttackedRockingBehaviourPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824CFE18
        private:
            CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviourPrototype,
                CD2_SIZE(cVehicleAttackedRockingBehaviourPrototype, 0xB0)
                CD2_OFFSET(cVehicleAttackedRockingBehaviourPrototype, m_fUnknown90, 0x90)
                CD2_OFFSET(cVehicleAttackedRockingBehaviourPrototype, m_fUnknownA4, 0xA4))
        };
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknownC0; // 0xC0
        unsigned char m_unmodelledC4[0xD0 - 0xC4];

        // 0xD0: the size the class registrar gives.
        CD2_LAYOUT_CHECKS(cVehicleAttackedRockingBehaviour,
            CD2_SIZE(cVehicleAttackedRockingBehaviour, 0xD0)
            CD2_OFFSET(cVehicleAttackedRockingBehaviour, m_nUnknownC0, 0xC0))
    };
}

#endif

