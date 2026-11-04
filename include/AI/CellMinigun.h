// AI::CellMinigun (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824C3228) calls NPCArmedBehaviour's constructor (0x824A8070), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CELLMINIGUN_H
#define AI_CELLMINIGUN_H

#include "AI/NPCArmedBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class CellMinigun : public NPCArmedBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellMinigunClass;

    private:
        unsigned int m_nUnknownF0; // 0xF0
        unsigned char m_padF4[0x100 - 0xF4];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline CellMinigun() : m_nUnknownF0(0) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(CellMinigun,
            CD2_SIZE(CellMinigun, 0x100)
            CD2_OFFSET(CellMinigun, m_nUnknownF0, 0xF0))
    };
}

#endif

