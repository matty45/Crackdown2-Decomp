#ifndef AI_CBASEJUMPERMISSION_H
#define AI_CBASEJUMPERMISSION_H

#include "AI/cMission.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
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

        cBaseJumperMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBaseJumperMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82459568
        virtual void Deactivate(); // cRegisteredClass 3: 0x82459618
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82489260
    };
}

#endif

