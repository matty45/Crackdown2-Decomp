// AI::cFreakExplodeEvent: no extra storage beyond cBasePatrolRouteEvent (CD2 factories allocate 0x90).
// Names/base from RuffKing's patrol-route event headers; runtime descriptor ID from CD2's initializer.
#ifndef AI_CFREAKEXPLODEEVENT_H
#define AI_CFREAKEXPLODEEVENT_H

#include "AI/cBasePatrolRouteEvent.h"
#include "cd2/memory.h"

namespace AI
{
    class cFreakExplodeEvent : public cBasePatrolRouteEvent
    {
    public:
        static const Fun_Runtime::cClass *ms_pcFreakExplodeEventClass;

        cFreakExplodeEvent() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer.
            static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x9F023, "cFreakExplodeEvent", 0x90);
            return *descriptor;
        }

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2 primary slot 16 points to 0x827E56A8, returning event type 0.
        virtual unsigned char RetEventType() const { return 0; }

        CD2_LAYOUT_CHECKS(cFreakExplodeEvent, CD2_SIZE(cFreakExplodeEvent, 0x90))
    };
}

#endif
