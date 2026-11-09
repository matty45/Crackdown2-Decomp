// STAND-IN: descriptive class/global names follow CD2's AIE_EQUIPMENT_LOST registration (0x82F7B120).
// Construction at 0x823EFF18 calls cAIEvent for a 0x44-byte object and installs table 0x820FC024,
// whose slot 1 is 0x823EC840. It adds no fields or virtual slots.
#ifndef AI_CEQUIPMENTLOSTEVENT_H
#define AI_CEQUIPMENTLOSTEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cEquipmentLostEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cEquipmentLostEvent, CD2_SIZE(cEquipmentLostEvent, 0x44))
    };
}
// Registrar at 0x83818D94; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cEquipmentLostEvent> g_cEquipmentLostEvent;
#endif
