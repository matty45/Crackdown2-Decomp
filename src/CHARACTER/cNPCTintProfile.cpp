// CHARACTER/cNPCTintProfile.cpp: byte-exact against Crackdown 2 (title update), all 7 functions.
// Decompiled in the whole-file pilot (2026-10-23, Sonnet 5.5, 17 harness runs); see docs/feasibility.md.
//   0x8255DFE8 constructor        0x821D0300 HandleAttributes (moved to the hot region by the link order list)
//   0x8255DF80 MakeNew            0x8255DFD8 RetClassName
//   0x821D0A20 scalar deleting destructor (compiler-generated, emitted here)
//   0x82FAF4E0 / 0x8303D140 dynamic initializer / at-exit destructor of cNPCTintProfileRegistrar
#include "CHARACTER/cNPCTintProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const char *const cNPCTintProfile::pcNPCTintProfileClassID = "cNPCTintProfile";

    cNPCTintProfile::cNPCTintProfile(const RWS::CAttributePacket &packet)
    {
        m_nPaletteSize = 1;
        m_anPalette[0].c = 0xFFFFFFFF;
        m_EventHandler.Register(this, packet.GetInstanceId());
    }

    const char *cNPCTintProfile::RetClassName() const
    {
        return pcNPCTintProfileClassID;
    }

    void cNPCTintProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, pcNPCTintProfileClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 8:
                m_nPaletteSize = (unsigned char)(it->GetAs_UInt32() >> 24);
                break;
            case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
                {
                    int n = it->GetCommandId();
                    unsigned int x = it->GetAs_UInt32();
                    m_anPalette[n].c = (x >> 24) | ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000) | (x << 24);
                }
            }
        }
    }

    RWS::CAttributeHandler *cNPCTintProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cNPCTintProfile(packet);
    }

    static RWS::CClassFactory::CRegistrar cNPCTintProfileRegistrar(
        "cNPCTintProfile", cNPCTintProfile::MakeNew, 0x50, false);
}
