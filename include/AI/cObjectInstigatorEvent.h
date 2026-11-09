// AI::cObjectInstigatorEvent (Crackdown 2): STAND-IN; the class name is ours (no reference build has this event, and
// CD2 does not name it). The method and field names are CD2's script names. Evidence:
//   - CD2's registration function 0x8243D9C0 registers "RetObject" (0x823E7C18, the getter of a safe pointer at 0x44;
//     see AI/cDamageTakenEvent.h) and then "RetInstigator" (0x823E7A88), which returns the object pointer at 0x60
//     converted to the object (null stays null, else minus 0x1C): a second safe pointer, at 0x54.
//   - The pointee types are not known; every instigator in the reference builds' events is a
//     safe pointer to AI::cCharacterEntityIF, so this one is too, and the object is a cNonGameBase.
//   - 0x823E7A88 lies in cAiPlayer.cpp's range (kept from cAiPlayer's object), so src/AI/cAiPlayer.cpp defines it.
#ifndef AI_COBJECTINSTIGATOREVENT_H
#define AI_COBJECTINSTIGATOREVENT_H

#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/safedeletablepointer.h"
#include "cd2/layout.h"

namespace AI
{
    class cObjectInstigatorEvent : public cAIEvent
    {
    public:
        // CD2 constructor 0x823EC280 stores object first and instigator second after the shared event base.
        cObjectInstigatorEvent(Fun_Runtime::cScriptHost *source, cCharacterEntityIF *instigator, cNonGameBase *object);
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        cCharacterEntityIF *RetInstigator();
        // Shared/folded CD2 slot 7 at 0x823EC378 checks the source and first object safe pointers.
        virtual bool IsValid();

    protected:
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pObject;           // 0x44
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pInstigator; // 0x54

    public:
        CD2_LAYOUT_CHECKS(cObjectInstigatorEvent,
            CD2_OFFSET(cObjectInstigatorEvent, m_pObject, 0x44)
            CD2_OFFSET(cObjectInstigatorEvent, m_pInstigator, 0x54))
    };
}

// CD2 0x82F77DF8 registers this event as AIE_OBJECT_APPROACHING under AIEvent;
// primary slot 1 (0x823EC368) returns its registrar at 0x8381764C. Global name is ours.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cObjectInstigatorEvent> g_cObjectApproachingEvent;

#endif // AI_COBJECTINSTIGATOREVENT_H
