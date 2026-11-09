// AI::cAIEvent: CD2 constructor 0x822137C0 establishes cScriptHost at +0 and cLinkedListItem at +0x1C.
// Unlike the later reference builds, CD2 events are script hosts. The primary table 0x820FAD60 has nine slots;
// cScriptHost supplies 0..5, ApplyFilter is 6, IsValid is 7, and the unresolved integer virtual is 8.
// The constructor stores type at +0x28, builds the source safe pointer at +0x2C, and stores subscription/time
// at +0x3C/+0x40. Its callers pass the source's script-host subobject (e.g. 0x82225D74 adds +0x1C).
// RetSource (0x823E7A80) returns that script pointer without a game-object adjustment. Reference builds name
// m_pSource, m_pSubscription, m_eEventType, m_nTimeStamp, ApplyFilter and IsValid; slot-8's name remains unknown.
#ifndef AI_CAIEVENT_H
#define AI_CAIEVENT_H

#include "fun_runtime/scripthost.h"
#include "fun_runtime/linkedlistitem.h"
#include "fun_runtime/safedeletablepointer.h"
#include "cd2/layout.h"

namespace AI
{
    class cAIEventSubscription;

    class cAIEvent : public Fun_Runtime::cScriptHost, public Fun_Runtime::cLinkedListItem
    {
    public:
        cAIEvent(unsigned int eventType, Fun_Runtime::cScriptHost *source); // CD2 0x822137C0
        virtual ~cAIEvent(); // CD2 0x823E5890, called by event destructors
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetName() const;
        virtual void Slot5(); // CD2 0x8243E310 registers this event's script methods
        virtual bool ApplyFilter(cAIEventSubscription &);
        virtual bool IsValid() { return m_pSource != 0; }
        virtual int vf8(); // CD2 0x82604740 returns -1; purpose unrecovered

        Fun_Runtime::cScriptHost *RetSource() const;

    protected:
        unsigned int m_eEventType;
        Fun_Runtime::cSafeDeletablePointer<Fun_Runtime::cScriptHost> m_pSource;
        cAIEventSubscription *m_pSubscription;
        unsigned int m_nTimeStamp;

        CD2_LAYOUT_CHECKS(cAIEvent,
            CD2_SIZE(cAIEvent, 0x44)
            CD2_OFFSET(cAIEvent, m_eEventType, 0x28)
            CD2_OFFSET(cAIEvent, m_pSource, 0x2C)
            CD2_OFFSET(cAIEvent, m_pSubscription, 0x3C)
            CD2_OFFSET(cAIEvent, m_nTimeStamp, 0x40))
    };
}

#endif // AI_CAIEVENT_H
