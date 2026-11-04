#include "rws/attributes.h"
// VFX::cParticleEffectResourceHolder (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x830099C0) registers "cParticleEffectResourceHolder" with MakeNew (0x827EDB88) and size 0x90.
#ifndef VFX_CPARTICLEEFFECTRESOURCEHOLDER_H
#define VFX_CPARTICLEEFFECTRESOURCEHOLDER_H

namespace VFX
{
    class cParticleEffectResourceHolder
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CPARTICLEEFFECTRESOURCEHOLDER_H
