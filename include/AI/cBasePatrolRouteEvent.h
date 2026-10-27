#ifndef AI_CBASEPATROLROUTEEVENT_H
#define AI_CBASEPATROLROUTEEVENT_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cBasePatrolRouteEvent : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcBasePatrolRouteEventClass;

        cBasePatrolRouteEvent();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

