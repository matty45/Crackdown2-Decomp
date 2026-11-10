// VFX::cBarrier (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8278F0E8, from its registrars in CD2's
// initializer run); RuffKing declares the class in VFX/cBarrier.h and defines it in cBarrier.obj. The layout is partly
// modelled below.
#ifndef VFX_CBARRIER_H
#define VFX_CBARRIER_H

#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"
#include "cd2/layout.h"

namespace Fun_Runtime { class Mtx; }

namespace VFX
{
    class BarrierMesh;
    class cBarrierSettings;

    // Burn's base order agrees with CD2 constructor 0x8278F850: debug-page
    // subobject at +0x18. Instance storage is only partly modelled: the named fields below are
    // Burn's, at CD2's offsets (constructor 0x8278F850 clears them; SetMesh 0x827906F0 stores
    // the next mesh at 0x80, its settings at 0x84 (default 0xE4 when null) and sets 0xE1/0xE3).
    // Size 0x110 from MakeNew 0x8278F0E8 and the registrar.
    class cBarrier : public RWS::CAttributeHandler, public GDb::cDebugPageHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x8278F850, out of line; MakeNew (0x8278F0E8) calls it with this only.
        cBarrier();
        // Primary table 0x8214C584, slot 11.
        virtual const char *RetClassName() const;

        // CD2 0x827906F0.
        void SetMesh(BarrierMesh *mesh, const Fun_Runtime::Mtx &matrix, const cBarrierSettings *settings);
        // Inline in CD2: cFinalMissionBarrier's Create/Destroy (0x8284F640, 0x8284F720) access the fields directly.
        void Disable() { m_pNextBarrier = 0; m_pNextSettings = 0; }
        bool IsEnabled() const { return m_pNextBarrier != 0; }
        void EnableKillzone(const bool onoff) { m_KillzoneEnabled = onoff; }

        static cBarrier *ms_pInstance;

    private:
        unsigned char m_unmodelled1C[0x80 - 0x1C];
        BarrierMesh *m_pNextBarrier;
        const cBarrierSettings *m_pNextSettings;
        unsigned char m_unmodelled88[0xE0 - 0x88];
        bool m_CollisionEnabled;
        bool m_NextCollisionEnabled;
        bool m_RefreshAtSynchronise;
        bool m_KillzoneEnabled;
        const cBarrierSettings *m_pDefaultSettings;
        unsigned char m_unmodelledE8[0x110 - 0xE8];

        CD2_LAYOUT_CHECKS(cBarrier,
            CD2_SIZE(cBarrier, 0x110)
            CD2_OFFSET(cBarrier, m_unmodelled1C, 0x1C)
            CD2_OFFSET(cBarrier, m_pNextBarrier, 0x80)
            CD2_OFFSET(cBarrier, m_pNextSettings, 0x84)
            CD2_OFFSET(cBarrier, m_KillzoneEnabled, 0xE3)
            CD2_OFFSET(cBarrier, m_pDefaultSettings, 0xE4))
    };
}

#endif // VFX_CBARRIER_H
