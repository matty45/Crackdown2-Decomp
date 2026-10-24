// CHARACTER::cNPCTintProfile: palette of NPC tint colours, set from RWS attributes.
// Layout from the RuffKing PDB, confirmed against CD2 (size 0x50; vtable 0x82114610, 13 slots).
#ifndef CHARACTER_CNPCTINTPROFILE_H
#define CHARACTER_CNPCTINTPROFILE_H

#include <xtl.h>
#include <xnamath.h>
#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cNPCTintProfile : public RWS::CAttributeHandler
    {
    private:
        Editor::cGUIDEventHandler<cNPCTintProfile> m_EventHandler;
        _XMCOLOR m_anPalette[8];
        unsigned char m_nPaletteSize;
        static const unsigned char nPALETTE_CAPACITY = 8;

    public:
        static const char *const pcNPCTintProfileClassID;

        virtual const char *RetClassName() const;
        virtual void Destruct();
        cNPCTintProfile(const RWS::CAttributePacket &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        _XMCOLOR CalcTintColour(unsigned int) const;
        unsigned char RetNumTints() const;
        _XMCOLOR RetTintColour(unsigned char) const;

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const char *RetRWSClassName();

        // No user-declared destructor: CD2's scalar deleting destructor has no vptr stores (implicit destructor).

        CD2_LAYOUT_CHECKS(cNPCTintProfile,
            CD2_SIZE(cNPCTintProfile, 0x50)
            CD2_OFFSET(cNPCTintProfile, m_anPalette, 0x2C)
            CD2_OFFSET(cNPCTintProfile, m_nPaletteSize, 0x4C))
    };
}

#endif // CHARACTER_CNPCTINTPROFILE_H
