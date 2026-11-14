// STAND-IN: descriptive class/member names are ours. CD2 table 0x820FCF3C has
// six slots and no destructor: register/release a record, activate/deactivate it,
// a true-returning predicate, then an observer test (false by default).
// cCWSatchelCharge construction 0x8261A2E0 initializes this base at +0x9D0,
// with a null record at +4; its own table 0x82123C68 overrides only slot 5.
#ifndef AI_CPERCEPTIONCLIENT_H
#define AI_CPERCEPTIONCLIENT_H
#include "cd2/layout.h"
namespace AI
{
    class cCharacterEntityIF;
    class cPerceptionRecord;
    class cPerceptionClient
    {
    public:
        cPerceptionClient() : m_pPerceptionRecord(0) {}
        // The interface has no virtual destructor. Satchel cleanup restores the
        // base table inline and leaves record release to its explicit lifecycle.
        ~cPerceptionClient() {}
        virtual void RegisterPerceptionRecord();
        virtual void UnregisterPerceptionRecord();
        virtual void ActivatePerceptionRecord();
        virtual void DeactivatePerceptionRecord();
        virtual bool RetPerceptionFlag();
        // The satchel override reads the observer's cCharacterEntityIF AI-entity link at +0x504.
        virtual bool TestObserver(cCharacterEntityIF *, bool);
    protected:
        cPerceptionRecord *m_pPerceptionRecord;
        CD2_LAYOUT_CHECKS(cPerceptionClient,
            CD2_SIZE(cPerceptionClient, 8)
            CD2_OFFSET(cPerceptionClient, m_pPerceptionRecord, 4))
    };
}
#endif
