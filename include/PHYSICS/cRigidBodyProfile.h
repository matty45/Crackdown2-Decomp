// PHYSICS::cRigidBodyProfile: bases and members from RuffKing. CD2's destructor (0x826A4368) restores the tables at
// 0 and at cNonGameBase's subobjects (0x260..0x298), unlinks and unregisters the event at 0x2F8, frees the wide
// string at 0x2DC, calls ~cNonGameBase and restores cRigidBodyData's table. Size 0x300 (registrar).
#ifndef PHYSICS_cRigidBodyProfile_H
#define PHYSICS_cRigidBodyProfile_H

#include "PHYSICS/cRigidBodyData.h"
#include "gom/non_game_base.h"
#include "fun_runtime/string.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace PHYSICS
{
    class cRigidBodyProfile : public cRigidBodyData, public cNonGameBase
    {
    public:
        // CD2 0x826A4250: MakeNew (0x826A4200) calls it out of line with only this.
        cRigidBodyProfile();
        virtual ~cRigidBodyProfile();
        // CD2 0x826A4358: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        Fun_Runtime::cString m_sProfileName;        // 0x2DC
        RWS::CEventId m_Msg_Return_RB_Self;          // 0x2F8

        CD2_LAYOUT_CHECKS(cRigidBodyProfile,
            CD2_SIZE(cRigidBodyProfile, 0x300)
            CD2_OFFSET(cRigidBodyProfile, m_sProfileName, 0x2DC)
            CD2_OFFSET(cRigidBodyProfile, m_Msg_Return_RB_Self, 0x2F8))
    };
}

#endif
