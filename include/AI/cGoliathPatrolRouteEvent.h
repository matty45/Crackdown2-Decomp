#ifndef AI_CGOLIATHPATROLROUTEEVENT_H
#define AI_CGOLIATHPATROLROUTEEVENT_H

#include "AI/cBasePatrolRouteEvent.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    // RuffKing's base. CD2's table (0x8210A7B0) holds this class's RetClass, IsA and RetClassName in slots 11 to 13, where
    // cBasePatrolRouteEvent declares them.
    class cGoliathPatrolRouteEvent : public cBasePatrolRouteEvent
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F95110);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cGoliathPatrolRouteEventClass = new Fun_Runtime::cClass(0x9F01E, "cGoliathPatrolRouteEvent", 0xA0);
            return *cGoliathPatrolRouteEventClass;
        }
        static const Fun_Runtime::cClass *ms_pcGoliathPatrolRouteEventClass;

        cGoliathPatrolRouteEvent();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cGoliathPatrolRouteEvent's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824C0118
    };
}

#endif

