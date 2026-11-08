#include "gom/object_prototype.h"
#ifndef AI_CELLROCKET_H
#define AI_CELLROCKET_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/NPCArmedBehaviour.h"

namespace AI
{
    class CellRocket : public NPCArmedBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F963F8 names placement factory 0x824c3de8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pCellRocketClass;

        CellRocket();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

