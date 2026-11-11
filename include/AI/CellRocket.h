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
        // CD2: CellRocket's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824C4ED0
    private:
        CD2_LAYOUT_CHECKS(CellRocket,
            CD2_SIZE(CellRocket, 0x110)
            CD2_OFFSET(CellRocket, m_nUnknownF0, 0xF0)
            CD2_OFFSET(CellRocket, m_vUnknown100, 0x100))

    public:
        // CD2 table 0x8200BCC0 differs from NPCArmedBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824C3FE0
        virtual void OnExit(); // slot 69: 0x824C4118
        virtual void Slot73(); // slot 73: 0x824C43D0
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824C4268
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824C4440
        virtual void Slot79(); // slot 79: 0x824C4190
        virtual void Slot83(); // slot 83: 0x824C41E8
        virtual void vf98(); // slot 98: 0x824C3F20
        virtual void vf102(); // slot 102: 0x82580578
        virtual void vf103(); // slot 103: 0x82580578
        virtual void vf104(); // slot 104: 0x82580578
        virtual void vf105(); // slot 105: 0x824C46F0
        virtual void vf106(); // slot 106: 0x82580578
        virtual void vf108(); // slot 108: 0x824C4A88
        virtual void vf109(); // slot 109: 0x824C3C58
        virtual void vf110(); // slot 110: 0x82580578
        virtual void vf112(); // slot 112: 0x824C45D8
        virtual void vf114(); // slot 114: 0x824C4498
        virtual void vf117(); // slot 117: 0x824C4958
        virtual void vf123(); // slot 123: 0x824C45A0
    };
}

#endif

