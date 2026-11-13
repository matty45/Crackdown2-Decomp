#ifndef AI_CBASEJUMPERMISSION_H
#define AI_CBASEJUMPERMISSION_H

#include "AI/cMission.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"
#include "fun_runtime/vector.h"
#include "fun_runtime/vec3.h"

namespace AI
{
    class cLocalPlayerTrigger;

    // RuffKing's base. CD2's primary table (0x82105378) starts with this class's RetClass and IsA and holds its RetClassName
    // in slot 17, as cMission's does.
    class cBaseJumperMission : public cMission
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8DDC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cBaseJumperMissionClass = new Fun_Runtime::cClass(0xB4D9, "cBaseJumperMission", 0x400);
            return *cBaseJumperMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcBaseJumperMissionClass;

        // RuffKing's states.
        enum eBaseJumperMissionState
        {
            eBJState_Inactive = 0,
            eBJState_InChopper,
            eBJState_Falling,
            eBJState_FallComplete,
            eBJState_InLandingZone,
            eBJState_Landed,
            eBJState_Complete,
        };

        // Defined in the source file, where they keep the running mission in a file-local pointer: CD2 expands the
        // constructor into MakeNew (0x82488FB0) and the destructor into the deleting destructor (0x824890A8).
        cBaseJumperMission();
        virtual ~cBaseJumperMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBaseJumperMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82489260
        // Attribute-handler slot 1 (table 0x82105490): 0x82489150.
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        // RuffKing's fields; its size (0x400) is CD2's registrar size, and MakeNew initializes them at these offsets.
        Fun_Runtime::cVector<cLocalPlayerTrigger *> m_LandingZones;    // 0x3C0
        eBaseJumperMissionState m_eBJState;                             // 0x3D0
        Fun_Runtime::Vec3 m_vFallStartPos;                              // 0x3E0
        float m_fFallDist;                                              // 0x3F0
        CD2_LAYOUT_CHECKS(cBaseJumperMission,
            CD2_SIZE(cBaseJumperMission, 0x400)
            CD2_OFFSET(cBaseJumperMission, m_LandingZones, 0x3C0)
            CD2_OFFSET(cBaseJumperMission, m_eBJState, 0x3D0)
            CD2_OFFSET(cBaseJumperMission, m_vFallStartPos, 0x3E0)
            CD2_OFFSET(cBaseJumperMission, m_fFallDist, 0x3F0))
    };
}

#endif

