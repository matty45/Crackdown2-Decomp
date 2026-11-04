// AI::EquipmentDropBehaviour (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824D2B60) calls cPilotBase's constructor (0x824D32E0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_EQUIPMENTDROPBEHAVIOUR_H
#define AI_EQUIPMENTDROPBEHAVIOUR_H

#include "AI/cPilotBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class EquipmentDropBehaviour : public cPilotBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pEquipmentDropBehaviourClass;

    private:

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline EquipmentDropBehaviour() {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(EquipmentDropBehaviour,
            CD2_SIZE(EquipmentDropBehaviour, 0x140))
    };
}

#endif

