// Method-only STAND-IN: no object layout is modelled here.
// Burn's cTriggerManager supplies the names and signatures. CD2 0x8277EAB8
// creates the singleton at 0x83801044; 0x8277E660 dispatches its event counters.
#pragma once

namespace Trigger
{
    enum eTriggerEvent
    {
        // CD2 table 0x820E6F58, entry 39, names ChainReaction.
        eTriggerEvent_ChainReaction = 39,
        // CD2 table 0x820E6F58, entry 91, names PlayerApproachedExplosiveObject.
        eTriggerEvent_PlayerApproachedExplosiveObject = 91,
        // CD2 table entry 304 names UseGunTurretReminder.
        eTriggerEvent_UseGunTurretReminder = 304
    };

    class cTriggerManager
    {
    public:
        static cTriggerManager &Instance() { return *m_pInstance; }
        bool NotifyEvent(eTriggerEvent eEvent);

    protected:
        static cTriggerManager *m_pInstance;
    };
}
