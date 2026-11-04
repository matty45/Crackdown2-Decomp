#ifndef AI_CELLTURRET_H
#define AI_CELLTURRET_H

#include "fun_runtime/vec3.h"
#include "cd2/layout.h"
#include "AI/cChaseBehaviour.h"
#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class CellTurret : public cNonGameBase
    {
    public:
        // CD2 MakeNew (0x824C51B8) allocates 0xB0 bytes, calls AI::NPCBehaviourPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class CellTurretPrototype : public AI::NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline CellTurretPrototype(const RWS::CAttributePacket &packet)
                : AI::NPCBehaviourPrototype(packet) {}

        private:
            Fun_Runtime::Vec3 m_vUnknown90; // 0x90
            unsigned char m_padA0[0xB0 - 0xA0];

            CD2_LAYOUT_CHECKS(CellTurretPrototype,
                CD2_SIZE(CellTurretPrototype, 0xB0)
                CD2_OFFSET(CellTurretPrototype, m_vUnknown90, 0x90))
        };

        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellTurretClass;

        CellTurret();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

