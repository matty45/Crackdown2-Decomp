// Activity::cSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D1D00, MakeNew 0x823D1DA0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CSPAWNPOINT_H
#define ACTIVITY_CSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"
#include "editor/guid_event_handler.h"

namespace Activity
{
    class cSpawnPoint : public cSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSpawnPointClass;
        // CD2 0x823D1F80 receives only this; factories apply the packet afterwards.
        cSpawnPoint();
        virtual ~cSpawnPoint();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual cNonGameBase *Spawn();

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &);

    private:
        // Burn names the two byte fields. CD2 adds a typed GUID handler after
        // them; its constructor stores the shared GUID table at +0x54.
        unsigned char m_nGameImportance;
        unsigned char m_nInitialDamageFraction;
        Editor::cGUIDEventHandler<cSpawnPoint> m_EventHandler;

        CD2_LAYOUT_CHECKS(cSpawnPoint,
            CD2_SIZE(cSpawnPoint, 0x70)
            CD2_OFFSET(cSpawnPoint, m_nGameImportance, 0x50)
            CD2_OFFSET(cSpawnPoint, m_nInitialDamageFraction, 0x51)
            CD2_OFFSET(cSpawnPoint, m_EventHandler, 0x54))
    };
}

#endif // ACTIVITY_CSPAWNPOINT_H
