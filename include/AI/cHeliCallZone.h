#ifndef AI_CHELICALLZONE_H
#define AI_CHELICALLZONE_H

#include "ZoneManager/cPlayerTriggerCylinder.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    // RuffKing's base. CD2's table (0x82105878) has the trigger cylinder's 18 slots, then this class's RetClass, IsA,
    // RetClassName and Destruct in slots 18 to 21.
    class cHeliCallZone : public ZoneManager::cPlayerTriggerCylinder
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8EEC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cHeliCallZoneClass = new Fun_Runtime::cClass(0x85D0F, "cHeliCallZone", 0x1F0);
            return *cHeliCallZoneClass;
        }
        static const Fun_Runtime::cClass *ms_pcHeliCallZoneClass;
        // RuffKing name: the zone the player is in, set by OnPlayerEnter (CD2 0x8248AA18) and cleared by OnPlayerLeave.
        static cHeliCallZone *m_pCurrentCallZone;

        cHeliCallZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // cPlayerTriggerBase's pure virtuals.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // CD2: cHeliCallZone's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x821F8630
        virtual void InitTriggerZone(); // 14: 0x82787050
        virtual void TermTriggerZone(); // 15: 0x8248AA38
    };
}

#endif

