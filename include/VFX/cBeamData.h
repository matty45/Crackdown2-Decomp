// VFX::cBeamData: a beam's appearance, set from RWS attributes. Names, types and layout from RuffKing (cBeam.h),
// 0x88 bytes there and in CD2's registrar. CD2's MakeNew (0x82802208) inlines the default constructor; the
// destructor (0x828022D8) is out of line and frees m_sName.
#ifndef VFX_cBeamData_H
#define VFX_cBeamData_H

#include "rws/attributes.h"
#include "fun_runtime/stringc.h"
#include "cd2/layout.h"

namespace VFX
{
    class cBeamData : public RWS::CAttributeHandler
    {
    public:
        cBeamData()
            : m_fBeamWidth(0.0f), m_fBeamHeight(0.0f), m_fSpotWidth(0.0f), m_fSpotHeight(0.0f),
              m_fBeamTileLength(0.0f), m_fSpotTileLength(0.0f), m_fSpotSpeedModifier(0.0f),
              m_BeamColour1(0xFFFFFFFF), m_BeamColour2(0xFFFFFFFF), m_SpotColour1(0xFFFFFFFF),
              m_SpotColour2(0xFFFFFFFF)
        {
        }
        virtual ~cBeamData();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

        Fun_Runtime::cStringc m_sName;          // 0x18
        float m_fBeamWidth;                     // 0x34
        float m_fBeamHeight;                    // 0x38
        float m_fSpotWidth;                     // 0x3C
        float m_fSpotHeight;                    // 0x40
        float m_fPulseWidth;                    // 0x44
        float m_fPulseHeight;                   // 0x48
        float m_fPulseLength;                   // 0x4C
        float m_fInitVelocity;                  // 0x50
        float m_fBeamTileLength;                // 0x54
        float m_fSpotTileLength;                // 0x58
        float m_fSpotSpeedModifier;             // 0x5C
        float m_fPulseEmissionIntervalMin;      // 0x60
        float m_fPulseEmissionIntervalMax;      // 0x64
        float m_fPulseVelocityMin;              // 0x68
        float m_fPulseVelocityMax;              // 0x6C
        unsigned long m_BeamColour1;            // 0x70
        unsigned long m_BeamColour2;            // 0x74
        unsigned long m_SpotColour1;            // 0x78
        unsigned long m_SpotColour2;            // 0x7C
        unsigned long m_PulseColour1;           // 0x80
        unsigned long m_PulseColour2;           // 0x84

        CD2_LAYOUT_CHECKS(cBeamData,
            CD2_SIZE(cBeamData, 0x88)
            CD2_OFFSET(cBeamData, m_sName, 0x18)
            CD2_OFFSET(cBeamData, m_fBeamWidth, 0x34)
            CD2_OFFSET(cBeamData, m_BeamColour1, 0x70))
    };
}

#endif
