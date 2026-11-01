// AI::cReaperPropAttackEvent: no extra storage beyond cBasePatrolRouteEvent (CD2 factories allocate 0x90).
// Names/base from RuffKing's patrol-route event headers; runtime descriptor ID from CD2's initializer.
#ifndef AI_CREAPERPROPATTACKEVENT_H
#define AI_CREAPERPROPATTACKEVENT_H

#include "AI/cBasePatrolRouteEvent.h"
#include "cd2/memory.h"

namespace AI
{
    class cReaperPropAttackEvent : public cBasePatrolRouteEvent
    {
    public:
        static const Fun_Runtime::cClass *ms_pcReaperPropAttackEventClass;

        cReaperPropAttackEvent() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer.
            static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x9F022, "cReaperPropAttackEvent", 0x90);
            return *descriptor;
        }

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2 primary slot 16 points to 0x8288F788, returning event type 3.
        virtual unsigned char RetEventType() const { return 3; }

        CD2_LAYOUT_CHECKS(cReaperPropAttackEvent, CD2_SIZE(cReaperPropAttackEvent, 0x90))
    };
}

#endif
