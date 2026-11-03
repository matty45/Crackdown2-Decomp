#ifndef GangManager_cTurretDataPrototype_H
#define GangManager_cTurretDataPrototype_H

#include "rws/attributes.h"
#include "gom/object_prototype.h"
#include "editor/guid_event_handler.h"

namespace GangManager
{
    class cPedestrainDataPrototype;
    // RuffKing layout; CD2 destructor 0x82678720 frees the array at 0x20 and destroys the handler at 0x2C.
    class cTurretDataPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual ~cTurretDataPrototype();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        GOM::cObjectPrototype *m_pTurretBasePrototype;
        GOM::cObjectPrototype *m_pTurretWeaponPrototype;
        cPedestrainDataPrototype **m_apGunners;
        int m_nNumGunners;
        int m_nGangStorageIndex;
        Editor::cGUIDEventHandler<cTurretDataPrototype> m_EventHandler;
        CD2_LAYOUT_CHECKS(cTurretDataPrototype,
            CD2_SIZE(cTurretDataPrototype, 0x40)
            CD2_OFFSET(cTurretDataPrototype, m_apGunners, 0x20)
            CD2_OFFSET(cTurretDataPrototype, m_EventHandler, 0x2C))
    };
}

#endif
