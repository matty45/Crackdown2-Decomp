// STAND-IN: reference cSoundEvent hierarchy and member name. CD2 constructor 0x824409C0 calls cAIEvent's
// constructor and stores volume at +0x44. Its table 0x82100180 adds slots 9..13 in reference order.
#ifndef AI_CSOUNDEVENT_H
#define AI_CSOUNDEVENT_H
#include "AI/cAIEvent.h"
class cNonGameBase;
namespace AI
{
    class cCharacterEntityIF;
    class cSoundEvent : public cAIEvent
    {
    public:
        cSoundEvent(unsigned int eventType, Fun_Runtime::cScriptHost *source, float volume);
        virtual Fun_Runtime::Vec3 RetScriptPosition() const;
        virtual cCharacterEntityIF *RetInstigator();
        virtual bool CanHearThisSound(cCharacterEntityIF *);
        virtual bool Concerns(cNonGameBase *);
    protected:
        virtual int RetDeafnessLODLevel(); // enum return type not recovered in this stand-in
        virtual float RetDistance(const Fun_Runtime::Vec3 &);
        float m_fVolume;
        CD2_LAYOUT_CHECKS(cSoundEvent,
            CD2_SIZE(cSoundEvent, 0x48)
            CD2_OFFSET(cSoundEvent, m_fVolume, 0x44))
    };
}
#endif
