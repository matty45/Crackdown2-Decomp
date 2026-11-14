// Vehicle::cAgencyBuggyPrototype (Crackdown 2): name, base cAgencyCarPrototype, members and size (0x550) from RuffKing.
// CD2's cAgencyBuggy::MakeNew (0x826E98D0) allocates 0x550 bytes, calls cCarPrototype's constructor (0x826B7BE0),
// installs table 0x82136B00, zeroes the suspension block at 0x4C0 (sixteen doublewords) and clears 0x540 and 0x544,
// as RuffKing's constructor does. Slot 5 is Init at 0x826E9AE0.
#ifndef VEHICLE_CAGENCYBUGGYPROTOTYPE_H
#define VEHICLE_CAGENCYBUGGYPROTOTYPE_H
#include "Vehicle/cAgencyCarPrototype.h"
#include <string.h>
namespace Vehicle
{
    class cAgencyBuggyPrototype : public cAgencyCarPrototype
    {
    public:
        // __forceinline: CD2 inlines it into MakeNew; /Ob1 declines it otherwise (docs/matching-notes.md).
        __forceinline cAgencyBuggyPrototype(const RWS::CAttributePacket &packet)
            : cAgencyCarPrototype(packet)
        {
            memset(&m_BuggySusp, 0, sizeof(m_BuggySusp));
            m_pTurretWeaponPrototype = 0;
            m_bTurretDataChanged = false;
        }
        virtual void HandleAttributes(const RWS::CAttributePacket &); // CD2 primary slot 1: 0x826E9A08.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        // RuffKing's suspension description of one buggy wheel.
        struct tSuspensionParams
        {
            unsigned char nUSpringFrameID;
            unsigned char nMSpringFrameID;
            unsigned char nDSpringFrameID;
            unsigned char nUWishboneFrameID;
            unsigned char nDWishboneFrameID;
            unsigned char nKnuckleFrameID;
            unsigned char nWheelComponentID;
            unsigned char nDWheelComponentID;
            float fLRMult;
            float fWheelWidth;
            float fWheelPivotOffset;
            float fWishBoneLength;
            float fSpringLenRecip;
        };
        struct tBuggySuspensionParams
        {
            tSuspensionParams aSuspParam[4];
            float fMaxFanRotSpeed;
            float fMaxCogRotSpeed;
            float fOneOverMaxRPM;
            unsigned char nEngineCog01FrameID;
            unsigned char nEngineCog02FrameID;
            unsigned char nEngineFanFrameID;
        };

        tBuggySuspensionParams m_BuggySusp;                 // 0x4C0
        GOM::cObjectPrototype *m_pTurretWeaponPrototype;    // 0x540
        bool m_bTurretDataChanged;                          // 0x544

        CD2_LAYOUT_CHECKS(cAgencyBuggyPrototype,
            CD2_SIZE(cAgencyBuggyPrototype, 0x550)
            CD2_OFFSET(cAgencyBuggyPrototype, m_BuggySusp, 0x4C0)
            CD2_OFFSET(cAgencyBuggyPrototype, m_pTurretWeaponPrototype, 0x540)
            CD2_OFFSET(cAgencyBuggyPrototype, m_bTurretDataChanged, 0x544))
    };
}
#endif
