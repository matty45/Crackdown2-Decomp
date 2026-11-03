#ifndef GangManager_cVehicleDataPrototype_H
#define GangManager_cVehicleDataPrototype_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"

namespace GangManager
{
    // STAND-IN: CD2 MakeNew allocates 0x58; destructor 0x82678DD0 frees the pointer array
    // at 0x24, then destroys the GUID handler at 0x44. Other members remain unmodelled.
    class cVehicleDataPrototype : public RWS::CAttributeHandler
    {
    public:
        virtual ~cVehicleDataPrototype();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        unsigned char m_unmodelled18[0x24 - 0x18];
        void **m_apOccupants; // descriptive name ours; array element type is not recovered
        unsigned char m_unmodelled28[0x44 - 0x28];
        Editor::cGUIDEventHandler<cVehicleDataPrototype> m_EventHandler;
        CD2_LAYOUT_CHECKS(cVehicleDataPrototype,
            CD2_SIZE(cVehicleDataPrototype, 0x58)
            CD2_OFFSET(cVehicleDataPrototype, m_apOccupants, 0x24)
            CD2_OFFSET(cVehicleDataPrototype, m_EventHandler, 0x44))
    };
}

#endif
