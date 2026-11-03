#ifndef GameManagement_cArenaBarrier_H
#define GameManagement_cArenaBarrier_H

#include "rws/attributes.h"

namespace VFX { class BarrierMesh; class cBarrierSettings; }

namespace GameManagement
{
    class cArenaBarrier : public RWS::CAttributeHandler
    {
    public:
        cArenaBarrier() : m_pBarrierMesh(0), m_pBarrierSettings(0) {}
        // CD2 0x8284EEC0 stores the derived vptr before ~CAttributeHandler.
        virtual ~cArenaBarrier() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        // Burn/RuffKing names; CD2 MakeNew clears these two pointers at 0x18/0x1C.
        VFX::BarrierMesh *m_pBarrierMesh;
        const VFX::cBarrierSettings *m_pBarrierSettings;
        CD2_LAYOUT_CHECKS(cArenaBarrier,
            CD2_SIZE(cArenaBarrier, 0x20)
            CD2_OFFSET(cArenaBarrier, m_pBarrierMesh, 0x18)
            CD2_OFFSET(cArenaBarrier, m_pBarrierSettings, 0x1C))
    };
}

#endif
