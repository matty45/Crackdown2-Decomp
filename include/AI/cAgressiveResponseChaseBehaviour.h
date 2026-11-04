#ifndef AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H
#define AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H

#include "cd2/layout.h"
#include "AI/cChaseBehaviour.h"
#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cAgressiveResponseChaseBehaviour : public cNonGameBase
    {
    public:
        // CD2 MakeNew (0x824C9210) allocates 0xB0 bytes, calls AI::NPCBehaviourPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class cAgressiveResponseChaseBehaviourPrototype : public AI::NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cAgressiveResponseChaseBehaviourPrototype(const RWS::CAttributePacket &packet)
                : AI::NPCBehaviourPrototype(packet), m_fUnknown90(0.0f), m_fUnknown94(0.0f), m_fUnknown98(0.0f), m_fUnknown9C(0.0f), m_fUnknownA0(0.0f), m_fUnknownA4(0.0f) {}

        private:
            float m_fUnknown90; // 0x90
            float m_fUnknown94; // 0x94
            float m_fUnknown98; // 0x98
            float m_fUnknown9C; // 0x9C
            float m_fUnknownA0; // 0xA0
            float m_fUnknownA4; // 0xA4
            unsigned char m_padA8[0xB0 - 0xA8];

            CD2_LAYOUT_CHECKS(cAgressiveResponseChaseBehaviourPrototype,
                CD2_SIZE(cAgressiveResponseChaseBehaviourPrototype, 0xB0)
                CD2_OFFSET(cAgressiveResponseChaseBehaviourPrototype, m_fUnknown90, 0x90))
        };

        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgressiveResponseChaseBehaviourClass;

        cAgressiveResponseChaseBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

