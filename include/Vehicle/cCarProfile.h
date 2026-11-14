// Vehicle::cCarProfile: base and m_Msg_Data_Modified from RuffKing. CD2's destructor unregisters the event at 0x8E0
// before cLandVehicleProfile's destructor. Size 0x8F0 (registrar).
#ifndef Vehicle_cCarProfile_H
#define Vehicle_cCarProfile_H

#include "Vehicle/cLandVehicleProfile.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace Vehicle
{
    class cCarProfile : public cLandVehicleProfile
    {
    public:
        // CD2's MakeNew (0x8269BEF0) inlines this constructor after cLandVehicleProfile's out-of-line one.
        // __forceinline: /Ob1 declines it otherwise (docs/matching-notes.md).
        __forceinline cCarProfile() {}
        virtual ~cCarProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x8269C210: CEventHandler slot 5 (this is the subobject at 0x278); RuffKing names the override.
        virtual void HandleEvents(RWS::CMsg &);
        virtual const char *RetClassName() const;

    private:
        RWS::CEventId m_Msg_Data_Modified;           // 0x8E0

        // CD2: cCarProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8269C160
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x8269C018
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8269C088
    private:
        CD2_LAYOUT_CHECKS(cCarProfile,
            CD2_SIZE(cCarProfile, 0x8F0)
            CD2_OFFSET(cCarProfile, m_Msg_Data_Modified, 0x8E0))
    };
}

#endif
