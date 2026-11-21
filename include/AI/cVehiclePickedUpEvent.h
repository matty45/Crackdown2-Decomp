// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77CF0 registers
// AIE_VEHICLE_PICKED_UP under AIEvent at 0x838175E0. Construction at 0x826D4CDC
// calls cAIEvent(type 0x65, source) in a 0x54-byte allocation and installs table 0x82135540.
// Script registration 0x8243D8A0 names RetCarrier, whose folded getter reads the safe pointer at +0x44.
// The carrier's +0x1C safe-deletable base proves the game-object representation; its concrete subtype
// remains unrecovered, so the payload is modelled through the shared cNonGameBase interface.
#ifndef AI_CVEHICLEPICKEDUPEVENT_H
#define AI_CVEHICLEPICKEDUPEVENT_H
#include "AI/cAIEvent.h"
#include "gom/non_game_base.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cVehiclePickedUpEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    private:
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pCarrier;
        CD2_LAYOUT_CHECKS(cVehiclePickedUpEvent,
            CD2_SIZE(cVehiclePickedUpEvent, 0x54)
            CD2_OFFSET(cVehiclePickedUpEvent, m_pCarrier, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cVehiclePickedUpEvent> g_cVehiclePickedUpEvent;
#endif
