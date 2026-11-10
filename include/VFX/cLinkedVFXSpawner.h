// VFX::cLinkedVFXSpawner (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x827FA6E0, MakeNew 0x827FA780, from its registrars in CD2's
// initializer run); RuffKing names the class in cLinkedVFXSpawner.obj. No layout or virtuals are modelled yet;
// base VFX::cAmbientVFXSpawnerBase from CD2's inheritance registrar.
#ifndef VFX_CLINKEDVFXSPAWNER_H
#define VFX_CLINKEDVFXSPAWNER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "VFX/cAmbientVFXSpawner.h"

namespace VFX
{
    class cLinkedVFXSpawner : public cAmbientVFXSpawnerBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcLinkedVFXSpawnerClass;
        // CD2 0x827FA780 inlines the 0x70-byte construction into MakeNew.
        __forceinline cLinkedVFXSpawner(const RWS::CAttributePacket &packet)
            : cAmbientVFXSpawnerBase(packet), m_fPlayDelay(0.0f), m_nPlayCount(-1),
              m_bInPlay(false), m_bUseScaleOverrides(false) {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        void HandleAttributes(const RWS::CAttributePacket &);
        void ForceStart(char nPlayCount);
        void ForceStop();

    protected:
        virtual bool CanSpawn() const;
        virtual bool SpawnVFX();
        virtual void OnVFXFinished();

        // RuffKing names and offsets, confirmed by the stores in CD2's factory.
        Editor::cGUIDEventHandler<cLinkedVFXSpawner> m_EventHandler;
        float m_fPlayDelay;
        char m_nPlayCount;
        bool m_bInPlay;
        bool m_bUseScaleOverrides;
        Fun_Runtime::Vec3 m_vScaleOverride;

        CD2_LAYOUT_CHECKS(cLinkedVFXSpawner,
            CD2_SIZE(cLinkedVFXSpawner, 0x70)
            CD2_OFFSET(cLinkedVFXSpawner, m_EventHandler, 0x40)
            CD2_OFFSET(cLinkedVFXSpawner, m_fPlayDelay, 0x54)
            CD2_OFFSET(cLinkedVFXSpawner, m_nPlayCount, 0x58)
            CD2_OFFSET(cLinkedVFXSpawner, m_bInPlay, 0x59)
            CD2_OFFSET(cLinkedVFXSpawner, m_bUseScaleOverrides, 0x5A)
            CD2_OFFSET(cLinkedVFXSpawner, m_vScaleOverride, 0x60))
    };
}

#endif // VFX_CLINKEDVFXSPAWNER_H
