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
        // Prototype interface from RuffKing; CD2 slot 5 at 0x8245B000. Instance fields are not modelled.
        class cMissionCriticalPropPrototype : public Prop::cProp::cPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 spawning initializer 0x82F873A0 names placement factory 0x8245af48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x8245B1E0.
        virtual ~cMissionCriticalProp();
    };
}

#endif // AI_CMISSIONCRITICALPROP_H
