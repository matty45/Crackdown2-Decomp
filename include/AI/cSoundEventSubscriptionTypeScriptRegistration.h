// STAND-IN: descriptive registrar name is ours; CD2 getter 0x824404B8 returns eSoundEventSubscriptionType, the enum
// RuffKing's cSoundEvent.h declares (kSEST_CanHear, kSEST_Concerns, kSEST_Crowd). Initializer 0x82F7A500 installs
// table 0x821001C0 on the four-byte object at 0x83818A58; at-exit 0x8303A600 restores the common table.
#ifndef AI_CSOUNDEVENTSUBSCRIPTIONTYPESCRIPTREGISTRATION_H
#define AI_CSOUNDEVENTSUBSCRIPTIONTYPESCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cSoundEventSubscriptionTypeScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cSoundEventSubscriptionTypeScriptRegistration,
                          CD2_SIZE(cSoundEventSubscriptionTypeScriptRegistration, 4))
    };
}
#endif
