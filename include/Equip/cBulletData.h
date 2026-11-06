#ifndef Equip_cBulletData_H
#define Equip_cBulletData_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"

namespace Equip
{
    // Bases from RuffKing; CD2's HandleEvents (0x826241C8) runs on the CEventHandler subobject at 0x18.
    class cBulletData : public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82623EB8 (MakeNew calls it).
        cBulletData();
        // CD2 0x826241C8: CEventHandler slot 5 (this is the subobject at 0x18). RuffKing names the override and the
        // event.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        unsigned char m_unmodelled1C[0x114 - 0x1C];
        RWS::CEventId m_RetreveEventID;             // 0x114 (RuffKing's name and offset)
        unsigned char m_unmodelled11C[0x138 - 0x11C];

        CD2_LAYOUT_CHECKS(cBulletData,
            CD2_SIZE(cBulletData, 0x138)
            CD2_OFFSET(cBulletData, m_RetreveEventID, 0x114))

    };
}

#endif
