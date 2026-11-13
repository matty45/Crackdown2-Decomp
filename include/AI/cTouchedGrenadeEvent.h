// STAND-IN: descriptive class/global names follow AIE_TOUCHED_GRENADE (initializer 0x82F79E68).
// CD2 construction at 0x823603F0 calls cAIEvent and builds the safe pointer at +0x44 in a 0x54-byte object;
// primary table 0x820FC0D8 slot 1 is 0x823EC890. Registration 0x82443C40 names the getter RetGrenade.
// The pointer uses cDynamicBody, the grenade-pointee type in the reference grenade sound/vocal events.
#ifndef AI_CTOUCHEDGRENADEEVENT_H
#define AI_CTOUCHEDGRENADEEVENT_H
#include "AI/cAIEvent.h"
#include "PHYSICS/cDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTouchedGrenadeEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual Fun_Runtime::Vec3 RetScriptPosition() const;
        virtual bool IsValid();
    protected:
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pGrenade;
        CD2_LAYOUT_CHECKS(cTouchedGrenadeEvent,
            CD2_SIZE(cTouchedGrenadeEvent, 0x54)
            CD2_OFFSET(cTouchedGrenadeEvent, m_pGrenade, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTouchedGrenadeEvent> g_cTouchedGrenadeEvent; // CD2 0x83818964
#endif
