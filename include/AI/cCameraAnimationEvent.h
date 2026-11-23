// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77B90 names
// descriptor 0x83817550 AIE_CAMANIM under AIEvent. Camera code at 0x82536C50
// allocates 0x44 bytes, calls cAIEvent with type 0x12, and installs table
// 0x820023D8 without adding a payload. Slot 1 is 0x8252CE78.
#ifndef AI_CCAMERAANIMATIONEVENT_H
#define AI_CCAMERAANIMATIONEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cCameraAnimationEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cCameraAnimationEvent, CD2_SIZE(cCameraAnimationEvent, 0x44))
    };
}
// Its descriptor initializer has no scaffolded source ownership yet.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cCameraAnimationEvent> g_cCameraAnimationEvent;
#endif
