// STAND-IN: descriptive class/global names follow AIE_EJECTED_FROM_VEHICLE (initializer 0x82F78050).
// CD2 constructor 0x823EC468 calls cAIEvent, constructs a safe pointer at +0x44 and installs
// primary table 0x820FBF68 (slot 1: 0x823EC518). Registration 0x8243DE78 names that pointer's getter
// RetEjector. Its script return wrapper is shared with the reference events' cCharacterEntityIF accessors.
#ifndef AI_CEJECTEDFROMVEHICLEEVENT_H
#define AI_CEJECTEDFROMVEHICLEEVENT_H
#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cEjectedFromVehicleEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pEjector;
        CD2_LAYOUT_CHECKS(cEjectedFromVehicleEvent,
            CD2_SIZE(cEjectedFromVehicleEvent, 0x54)
            CD2_OFFSET(cEjectedFromVehicleEvent, m_pEjector, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cEjectedFromVehicleEvent> g_cEjectedFromVehicleEvent; // CD2 0x83817728
#endif
