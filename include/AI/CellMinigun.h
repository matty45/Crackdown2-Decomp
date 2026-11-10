#include "gom/object_prototype.h"
#ifndef AI_CELLMINIGUN_H
#define AI_CELLMINIGUN_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCArmedBehaviour.h"
#include "cd2/layout.h"

namespace AI
{
    class CellMinigun : public NPCArmedBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F95FC0 names placement factory 0x824c3228.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellMinigunClass;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824C3228), which calls
        // NPCArmedBehaviour's constructor (0x824A8070) out of line and then initialises the fields below (names ours).
        __forceinline CellMinigun() : m_nUnknownF0(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknownF0; // 0xF0
        unsigned char m_unmodelledF4[0x100 - 0xF4];
        // 0x100: the size CellMinigun's class registrar gives.
        CD2_LAYOUT_CHECKS(CellMinigun,
            CD2_SIZE(CellMinigun, 0x100)
            CD2_OFFSET(CellMinigun, m_nUnknownF0, 0xF0))
    };
}

#endif

