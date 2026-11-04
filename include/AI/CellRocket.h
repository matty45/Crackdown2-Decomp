// AI::CellRocket (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824C3DE8) calls NPCArmedBehaviour's constructor (0x824A8070), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CELLROCKET_H
#define AI_CELLROCKET_H

#include "AI/NPCArmedBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class CellRocket : public NPCArmedBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellRocketClass;

    private:
        unsigned int m_nUnknownF0; // 0xF0
        unsigned int m_nUnknownF4; // 0xF4
        unsigned char m_padF8[0x100 - 0xF8];
        Fun_Runtime::Vec3 m_vUnknown100; // 0x100

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline CellRocket() : m_nUnknownF0(0), m_nUnknownF4(0), m_vUnknown100(Fun_Runtime::ZeroVec) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(CellRocket,
            CD2_SIZE(CellRocket, 0x110)
            CD2_OFFSET(CellRocket, m_nUnknownF0, 0xF0))
    };
}

#endif

