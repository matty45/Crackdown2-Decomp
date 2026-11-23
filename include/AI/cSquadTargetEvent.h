// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77A88 names
// descriptor 0x838174E4 AIE_SQUAD_TARGET under AIEvent. Squad code at 0x824D9510
// allocates 0x44 bytes, calls cAIEvent with type 6, then installs table
// 0x8210D2F0 without adding a payload. Its slot-1 getter is 0x824D82C0.
#ifndef AI_CSQUADTARGETEVENT_H
#define AI_CSQUADTARGETEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cSquadTargetEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cSquadTargetEvent, CD2_SIZE(cSquadTargetEvent, 0x44))
    };
}
// Its descriptor initializer has no scaffolded source ownership yet.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cSquadTargetEvent> g_cSquadTargetEvent;
#endif
