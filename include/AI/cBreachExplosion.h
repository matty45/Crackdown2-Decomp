#ifndef AI_cBreachExplosion_H
#define AI_cBreachExplosion_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"
#include "fun_runtime/class.h"
#include "fun_runtime/mtx.h"
#include "editor/guid_event_handler.h"

// Layout and member names from the reference cBreachExplosion header, checked
// against CD2 constructor 0x822C11B0: event interface +0x18, profile +0x1E,
// timers +0x24/+0x28, matrix +0x30 and GUID handler +0x70.
// Primary table 0x82003D80 puts RetClass/IsA before RetClassName at slots 11..13.

namespace AI
{
    class cBreachExplosion : public RWS::CSystemCommands, public RWS::CAttributeHandler,
        public RWS::CEventHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 initializer 0x82F899F8 stores this descriptor at 0x8381CA94.
        static const Fun_Runtime::cClass *ms_pcBreachExplosionClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual ~cBreachExplosion();
    public:
        // Out of line: CD2 0x822C11B0 (MakeNew calls it).
        cBreachExplosion();

    private:
        unsigned short m_nProfileID;
        bool m_bActive;
        float m_fActivationTimer;
        float m_fCurrentTimer;
        unsigned short m_nExplosionLevel;
        Fun_Runtime::Mtx m_mMat;
        Editor::cGUIDEventHandler<cBreachExplosion> m_EventHandler;

        CD2_LAYOUT_CHECKS(cBreachExplosion, CD2_SIZE(cBreachExplosion, 0x90)
            CD2_OFFSET(cBreachExplosion, m_nProfileID, 0x1E)
            CD2_OFFSET(cBreachExplosion, m_bActive, 0x20)
            CD2_OFFSET(cBreachExplosion, m_fActivationTimer, 0x24)
            CD2_OFFSET(cBreachExplosion, m_fCurrentTimer, 0x28)
            CD2_OFFSET(cBreachExplosion, m_nExplosionLevel, 0x2C)
            CD2_OFFSET(cBreachExplosion, m_mMat, 0x30)
            CD2_OFFSET(cBreachExplosion, m_EventHandler, 0x70))

    };
}

#endif
