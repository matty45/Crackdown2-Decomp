#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cBeaconProp (Crackdown 2): STAND-IN for the class name only. Base AI::cMissionCriticalProp, as in RuffKing's
// header; RetClassName (0x8245C278) is slot 11 of the vtable at 0x82103748, as cNonGameBase's RetClassName.
#ifndef AI_CBEACONPROP_H
#define AI_CBEACONPROP_H

#include "AI/cMissionCriticalProp.h"

namespace AI
{
    class cBeaconProp : public AI::cMissionCriticalProp
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cBeaconProp(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcBeaconPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CBEACONPROP_H
