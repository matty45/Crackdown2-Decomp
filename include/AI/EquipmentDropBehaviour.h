#include "gom/object_prototype.h"
#ifndef AI_EQUIPMENTDROPBEHAVIOUR_H
#define AI_EQUIPMENTDROPBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class EquipmentDropBehaviour : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F9BA00 names placement factory 0x824d2b60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pEquipmentDropBehaviourClass;

        EquipmentDropBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

