#ifndef AI_CCITYGLIDERMISSION_H
#define AI_CCITYGLIDERMISSION_H

#include "AI/cMission.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"
#include "fun_runtime/vector.h"
#include <xtl.h>

namespace AI
{
    class cCityGliderWaypoint;
    class cCityGliderMission;
    // RuffKing's singleton (CD2 0x838009C4): this class's constructor and destructor set and clear it, and code
    // outside the file (0x823C3C00) reads it.
    extern cCityGliderMission *g_pCityGliderMission;

    // RuffKing's base. CD2's primary table (0x82105538) starts with this class's RetClass and IsA and holds its RetClassName
    // in slot 17, as cMission's does.
    class cCityGliderMission : public cMission
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8E2E0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cCityGliderMissionClass = new Fun_Runtime::cClass(0xB4D8, "cCityGliderMission", 0x440);
            return *cCityGliderMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcCityGliderMissionClass;

        // CD2's MakeNew (0x824897A0) inlines this constructor after cMission's (0x824592E8); RuffKing's body (its
        // one-instance assert is compiled out).
        __forceinline cCityGliderMission()
        {
            g_pCityGliderMission = this;
            XMemSet(m_nProgress, 0, sizeof(m_nProgress));
            XMemSet(m_nLastCompletedTime, 0, sizeof(m_nLastCompletedTime));
        }
        // CD2's deleting destructor (0x824898F8) clears the singleton and frees the waypoint vectors inline.
        virtual ~cCityGliderMission()
        {
            g_pCityGliderMission = 0;
        }
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cCityGliderMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82459568
        virtual void Deactivate(); // cRegisteredClass 3: 0x82459618
    protected:
        // RuffKing's fields; size 0x440 from CD2's registrar (MakeNew allocates it).
        unsigned char m_nProgress[16];                                  // 0x3C0
        unsigned int m_nLastCompletedTime[16];                          // 0x3D0
        Fun_Runtime::cVector<cCityGliderWaypoint *> m_IslandWaypoints[3];  // 0x410
        CD2_LAYOUT_CHECKS(cCityGliderMission,
            CD2_SIZE(cCityGliderMission, 0x440)
            CD2_OFFSET(cCityGliderMission, m_nLastCompletedTime, 0x3D0)
            CD2_OFFSET(cCityGliderMission, m_IslandWaypoints, 0x410))
    };
}

#endif

