// Vehicle::cAgencySUVPrototype (Crackdown 2): name, base cAgencyCarPrototype, members and size (0x4D0) from RuffKing.
// CD2's cAgencySUV::MakeNew (0x826FB9C8) allocates 0x4D0 bytes, calls cCarPrototype's constructor (0x826B7BE0),
// installs table 0x8213813C and stores 1.0, 12.0, 0.5 and 2.0 at 0x4C0..0x4CC, as RuffKing's constructor does.
// Slot 5 is Init at 0x826FBC28.
#ifndef VEHICLE_CAGENCYSUVPROTOTYPE_H
#define VEHICLE_CAGENCYSUVPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
namespace Vehicle
{
    class cAgencySUVPrototype : public cAgencyCarPrototype
    {
    public:
        // __forceinline: CD2 inlines it into MakeNew; /Ob1 declines it otherwise (docs/matching-notes.md).
        __forceinline cAgencySUVPrototype(const RWS::CAttributePacket &packet)
            : cAgencyCarPrototype(packet), m_fCompressAcc(1.0f), m_fJumpAcc(12.0f), m_fCompressTime(0.5f),
              m_fMaxCompressTime(2.0f)
        {
        }
        virtual void HandleAttributes(const RWS::CAttributePacket &); // CD2 primary slot 1: 0x826FBA90.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        float m_fCompressAcc;       // 0x4C0
        float m_fJumpAcc;           // 0x4C4
        float m_fCompressTime;      // 0x4C8
        float m_fMaxCompressTime;   // 0x4CC

        CD2_LAYOUT_CHECKS(cAgencySUVPrototype,
            CD2_SIZE(cAgencySUVPrototype, 0x4D0)
            CD2_OFFSET(cAgencySUVPrototype, m_fCompressAcc, 0x4C0)
            CD2_OFFSET(cAgencySUVPrototype, m_fMaxCompressTime, 0x4CC))
    };
}
#endif
