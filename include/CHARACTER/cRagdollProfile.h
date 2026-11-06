#ifndef CHARACTER_cRagdollProfile_H
#define CHARACTER_cRagdollProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/eventid.h"
#include "fun_runtime/class.h"

// A static constant of this header (RuffKing: shared/character/cragdollprofile.h, initializer at line 29), so every
// object file that includes it has a copy; CD2 computes it from the object's g_GlobalConstants.
static const float nPART_PERCENT_WEIGHT = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1 / 12.0f;

namespace CHARACTER
{
    // Base cNonGameBase (CD2's inheritance registrar names it); CD2's HandleEvents (0x82575F38) runs on its
    // CEventHandler subobject at 0x18.
    class cRagdollProfile : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcRagdollProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82577D68 (MakeNew calls it).
        cRagdollProfile();
        // CD2 0x82575F38: CEventHandler slot 5 (this is the subobject at 0x18). RuffKing names the override and the
        // event.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        unsigned char m_unmodelled7C[0x39C - 0x7C];
        RWS::CEventId m_Msg_Return_Self;            // 0x39C (RuffKing 0x3CC)
        unsigned char m_unmodelled3A4[0x3B0 - 0x3A4];

        CD2_LAYOUT_CHECKS(cRagdollProfile,
            CD2_SIZE(cRagdollProfile, 0x3B0)
            CD2_OFFSET(cRagdollProfile, m_Msg_Return_Self, 0x39C))

    };
}

#endif
