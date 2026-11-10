#ifndef AI_CTRAININGROUTEEVENT_H
#define AI_CTRAININGROUTEEVENT_H

#include "AI/cBasePatrolRouteEvent.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // RuffKing's base. CD2's table (0x821049E0) holds this class's RetClass, IsA and RetClassName in slots 11 to 13, where
    // cBasePatrolRouteEvent declares them.
    class cTrainingRouteEvent : public cBasePatrolRouteEvent
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingRouteEventClass;

        cTrainingRouteEvent();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

