#ifndef AI_CBASEPATROLROUTEEVENT_H
#define AI_CBASEPATROLROUTEEVENT_H

#include "rws/systemcommands.h"
#include "rws/dynamicallocationpolicy.h"
#include "rws/eventhandler.h"
#include "fun_runtime/class.h"
#include "fun_runtime/mtx.h"
#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "cd2/memory.h"

namespace AI
{
    // CD2 layout from 0x824BFA80, with names/base order from RuffKing's cBasePatrolRouteEvent.h.
    class cBasePatrolRouteEvent : public RWS::CSystemCommands, public RWS::CAttributeHandler,
        public RWS::DynamicAllocationPolicy, public RWS::CEventHandler
    {
    public:
        static const Fun_Runtime::cClass *ms_pcBasePatrolRouteEventClass;
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 0x82F94C88 inlines this descriptor creation into the global initializer.
            static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x9F020, "cBasePatrolRouteEvent", 0x90);
            return *descriptor;
        }

        cBasePatrolRouteEvent();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);
        virtual unsigned char RetEventType() const;
        virtual const Fun_Runtime::Mtx &RetMatrix() const;
        virtual unsigned int RetNumRepetitions() const;
        virtual cBasePatrolRouteEvent *RetNextEvent() const;
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);

    protected:
        unsigned char m_EventType;
        Fun_Runtime::Mtx m_mMat;
        unsigned int m_nEventRepetitions;
        RWS::RWSGUID m_guidNextEvent;
        Editor::cGUIDEventHandler<cBasePatrolRouteEvent> m_EventHandler;

        CD2_LAYOUT_CHECKS(cBasePatrolRouteEvent,
            CD2_SIZE(cBasePatrolRouteEvent, 0x90)
            CD2_OFFSET(cBasePatrolRouteEvent, m_EventType, 0x1D)
            CD2_OFFSET(cBasePatrolRouteEvent, m_mMat, 0x20)
            CD2_OFFSET(cBasePatrolRouteEvent, m_nEventRepetitions, 0x60)
            CD2_OFFSET(cBasePatrolRouteEvent, m_guidNextEvent, 0x64)
            CD2_OFFSET(cBasePatrolRouteEvent, m_EventHandler, 0x74))
    };
}

#endif

