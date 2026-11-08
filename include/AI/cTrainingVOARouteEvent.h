#ifndef AI_CTRAININGVOAROUTEEVENT_H
#define AI_CTRAININGVOAROUTEEVENT_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    class cTrainingVOARouteEvent : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8D2F0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cTrainingVOARouteEventClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cTrainingVOARouteEvent", 0xA0);
            return *cTrainingVOARouteEventClass;
        }
        static const Fun_Runtime::cClass *ms_pcTrainingVOARouteEventClass;

        cTrainingVOARouteEvent();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

