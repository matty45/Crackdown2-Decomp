// STAND-IN: descriptive class/global names follow AIE_ATTACKED (initializer 0x82F78628).
// CD2 construction at 0x823E9E34 calls cAIEvent, builds the attacker safe pointer at +0x44 and copies
// the position to +0x60 in a 0x70-byte object; table 0x820FB138 has metadata getter 0x823E7AB0 at slot 1.
// Registration 0x8243E238 names RetAttacker. Its type follows the reference events' attacker pointers.
// Position is our member name: slot 3 (0x826B7D28) returns that vector, confirming its role and alignment.
#ifndef AI_CATTACKEDEVENT_H
#define AI_CATTACKEDEVENT_H
#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cAttackedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual Fun_Runtime::Vec3 RetScriptPosition() const;
        virtual bool IsValid();
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pAttacker;
        Fun_Runtime::Vec3 m_vecPosition;
        CD2_LAYOUT_CHECKS(cAttackedEvent,
            CD2_SIZE(cAttackedEvent, 0x70)
            CD2_OFFSET(cAttackedEvent, m_pAttacker, 0x44)
            CD2_OFFSET(cAttackedEvent, m_vecPosition, 0x60))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cAttackedEvent> g_cAttackedEvent; // CD2 0x8381798C
#endif
