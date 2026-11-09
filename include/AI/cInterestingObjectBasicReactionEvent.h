// STAND-IN: descriptive class/global names follow AIE_INTERESTING_OBJECT_BASIC_REACTION.
// CD2 initializer 0x82F78418 registers it under AIE_INTERESTING_OBJECT; construction at 0x823EFC64
// calls cInterestingObjectEvent's constructor and installs table 0x820FBFD4 (slot 1: 0x823EC618).
#ifndef AI_CINTERESTINGOBJECTBASICREACTIONEVENT_H
#define AI_CINTERESTINGOBJECTBASICREACTIONEVENT_H
#include "AI/cInterestingObjectEvent.h"
namespace AI
{
    class cInterestingObjectBasicReactionEvent : public cInterestingObjectEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cInterestingObjectBasicReactionEvent,
            CD2_SIZE(cInterestingObjectBasicReactionEvent, 0x54))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cInterestingObjectBasicReactionEvent> g_cInterestingObjectBasicReactionEvent; // CD2 0x838178B4
#endif
