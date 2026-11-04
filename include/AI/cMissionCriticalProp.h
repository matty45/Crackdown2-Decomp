#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cMissionCriticalProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8245AF38) is slot 11 of the vtable at 0x82102F88, as cNonGameBase's RetClassName.
#ifndef AI_CMISSIONCRITICALPROP_H
#define AI_CMISSIONCRITICALPROP_H

#include "Prop/cProp.h"

namespace AI
{
    class cMissionCriticalProp : public Prop::cProp
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cMissionCriticalProp(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CMISSIONCRITICALPROP_H
