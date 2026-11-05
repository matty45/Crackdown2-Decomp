#include "rws/attributes.h"
// VFX::cParticleEffectResourceHolder: CD2 stand-in. RuffKing names the base,
// resource-name vector and priority. CD2 MakeNew and destructor establish the
// vector at +0x7C and priority at +0x8C, total size 0x90.
// Its class-factory registrar (0x830099C0) registers "cParticleEffectResourceHolder" with MakeNew (0x827EDB88) and size 0x90.
#ifndef VFX_CPARTICLEEFFECTRESOURCEHOLDER_H
#define VFX_CPARTICLEEFFECTRESOURCEHOLDER_H

#include "gom/non_game_base.h"
#include "fun_runtime/vector.h"

namespace VFX
{
    class cParticleEffectResourceHolder : public cNonGameBase
    {
    public:
        // CD2 inlines this constructor into MakeNew, including the vector initialization.
        __forceinline cParticleEffectResourceHolder(const RWS::CAttributePacket &)
            : m_fDefaultPriority(0.0f) {}
        virtual ~cParticleEffectResourceHolder();
        static const Fun_Runtime::cClass *ms_pcParticleEffectResourceHolderClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    private:
        Fun_Runtime::cVector<const char *> m_vResources;
        float m_fDefaultPriority;

        CD2_LAYOUT_CHECKS(cParticleEffectResourceHolder,
            CD2_SIZE(cParticleEffectResourceHolder, 0x90)
            CD2_OFFSET(cParticleEffectResourceHolder, m_vResources, 0x7C)
            CD2_OFFSET(cParticleEffectResourceHolder, m_fDefaultPriority, 0x8C))
    };
}

#endif // VFX_CPARTICLEEFFECTRESOURCEHOLDER_H
