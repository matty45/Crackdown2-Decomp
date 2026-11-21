// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77D48 registers
// AIE_VEHICLE_DROPPED under AIEvent at 0x83817604. Construction at 0x826D4B7C
// calls cAIEvent(type 0x66, source) in a 0x54-byte allocation and installs table 0x82135564.
// Script registration 0x8243D8A0 names RetCarrier, whose folded getter reads the safe pointer at +0x44.
// The carrier's +0x1C safe-deletable base proves the game-object representation; its concrete subtype
// remains unrecovered, so the payload is modelled through the shared cNonGameBase interface.
#ifndef AI_CVEHICLEDROPPEDEVENT_H
#define AI_CVEHICLEDROPPEDEVENT_H
#include "AI/cAIEvent.h"
#include "gom/non_game_base.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cVehicleDroppedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    private:
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pCarrier;
        CD2_LAYOUT_CHECKS(cVehicleDroppedEvent,
            CD2_SIZE(cVehicleDroppedEvent, 0x54)
            CD2_OFFSET(cVehicleDroppedEvent, m_pCarrier, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cVehicleDroppedEvent> g_cVehicleDroppedEvent;
#endif
