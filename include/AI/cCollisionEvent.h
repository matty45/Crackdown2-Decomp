// STAND-IN: reference name/base/member. CD2 construction at 0x82323F44 calls
// cAIEvent(type 0x6A, source), installs table 0x8213248C and builds the object
// safe pointer at +0x44 in a 0x54-byte allocation. Initializer 0x82F79EC0
// registers AIE_COLLISION under AIEvent at 0x83818988. Slot 1 is 0x82684C68.
#ifndef AI_CCOLLISIONEVENT_H
#define AI_CCOLLISIONEVENT_H
#include "AI/cAIEvent.h"
#include "PHYSICS/cDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cCollisionEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool IsValid();
        // CD2 table 0x8213248C overrides the base's unresolved integer hook with 0x82684C78 (400).
        virtual int vf8();
    private:
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pObject;
        CD2_LAYOUT_CHECKS(cCollisionEvent,
            CD2_SIZE(cCollisionEvent, 0x54)
            CD2_OFFSET(cCollisionEvent, m_pObject, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cCollisionEvent> g_cCollisionEvent;
#endif
