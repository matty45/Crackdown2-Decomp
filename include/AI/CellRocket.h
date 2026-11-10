#include "gom/object_prototype.h"
#ifndef AI_CELLROCKET_H
#define AI_CELLROCKET_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCArmedBehaviour.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace AI
{
    class CellRocket : public NPCArmedBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F963F8 names placement factory 0x824c3de8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellRocketClass;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824C3DE8), which calls
        // NPCArmedBehaviour's constructor (0x824A8070) out of line and then initialises the fields below (names ours).
        __forceinline CellRocket() : m_nUnknownF0(0), m_nUnknownF4(0), m_vUnknown100(Fun_Runtime::ZeroVec) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknownF0;       // 0xF0
        unsigned int m_nUnknownF4;       // 0xF4
        Fun_Runtime::Vec3 m_vUnknown100; // 0x100 (aligned 16)
        // 0x110: the size CellRocket's class registrar gives.
        CD2_LAYOUT_CHECKS(CellRocket,
            CD2_SIZE(CellRocket, 0x110)
            CD2_OFFSET(CellRocket, m_nUnknownF0, 0xF0)
            CD2_OFFSET(CellRocket, m_vUnknown100, 0x100))
    };
}

#endif

