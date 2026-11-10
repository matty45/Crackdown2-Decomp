#ifndef GameManagement_cHUDPingProfile_H
#define GameManagement_cHUDPingProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cHUDPingProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2's deleting wrapper inlines the destructor and stores the derived vptr.
        virtual ~cHUDPingProfile() {}
        cHUDPingProfile(const RWS::CAttributePacket &);
        enum LoadParameterTypes
        {
            CMD_PingTime_Weapon,
            CMD_PingTime_Grenade,
            CMD_PingTime_Targeted,
            CMD_PingTime_Damaged
        };
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        // RuffKing names/count; CD2 MakeNew clears 16 bytes at 0x837C2610.
        static float m_aPingTime[4];
        // CD2: cHUDPingProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x8288FB78
    private:
        CD2_LAYOUT_CHECKS(cHUDPingProfile, CD2_SIZE(cHUDPingProfile, 0x18))
    };
}

#endif
