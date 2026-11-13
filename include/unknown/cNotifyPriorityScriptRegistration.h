// STAND-IN: descriptive registrar name is ours; CD2 getter 0x824549E8 returns eNotifyPriority, and RegisterValues 0x82454B20 writes
// its 6 values. Initializer 0x82F85A38 installs table 0x8210223C on the four-byte object at 0x8381C034; at-exit 0x8303AE28
// restores the common table.
#ifndef UNKNOWN_CNOTIFYPRIORITYSCRIPTREGISTRATION_H
#define UNKNOWN_CNOTIFYPRIORITYSCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace unknown
{
    class cNotifyPriorityScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cNotifyPriorityScriptRegistration, CD2_SIZE(cNotifyPriorityScriptRegistration, 4))
    };
}
#endif
