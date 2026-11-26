// STAND-IN: RuffKing names/member order (Sim/cTimeOfDay.h). CD2 constructor 0x82773E90 establishes
// a four-byte registered-class interface followed by time +4, ID +8, repeat +0xC, event ID +0x10 and days +0x18.
// Table 0x821478D8 is RetClass, IsA, script metadata; descriptor 0x82773C40 gives size 0x1C.
// Slot 2 (0x82773B18) returns descriptor 0x8385187C; the destructor is nonvirtual, as in RuffKing.
// CD2's script metadata registers cScriptHost as its parent (0x83002028), but its physical C++ base is
// cRegisteredClass: a 0x1C-byte cScriptHost would overlap the constructor's first scalar stores.
#ifndef SIM_CTODNOTIFICATION_H
#define SIM_CTODNOTIFICATION_H
#include "fun_runtime/class.h"
#include "fun_runtime/cScriptTypeRegistration.h"
#include "rws/eventid.h"
namespace Sim
{
    class cTODNotification : public Fun_Runtime::cRegisteredClass
    {
    public:
        cTODNotification(float time, bool repeat);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTODNotificationClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // RuffKing's accessors. The destructor is compiler-generated there; CD2's tree node cleanup (0x82776898)
        // destroys the event ID directly.
        unsigned int RetID() { return m_ID; }
        RWS::CEventId &RetEventID() { return m_EventID; }
        bool operator<(const cTODNotification &) const;
    private:
        float m_fTime;
        unsigned int m_ID;
        bool m_bRepeat;
        RWS::CEventId m_EventID;
        int m_NumDaysPassed;
        static unsigned int ms_NextFreeID;
        CD2_LAYOUT_CHECKS(cTODNotification,
            CD2_SIZE(cTODNotification, 0x1C)
            CD2_OFFSET(cTODNotification, m_fTime, 4)
            CD2_OFFSET(cTODNotification, m_ID, 8)
            CD2_OFFSET(cTODNotification, m_bRepeat, 0xC)
            CD2_OFFSET(cTODNotification, m_EventID, 0x10)
            CD2_OFFSET(cTODNotification, m_NumDaysPassed, 0x18))
    };
}
#endif
