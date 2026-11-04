#include "cd2/layout.h"
#include "rws/attributes.h"
// VFX::cParticleEffectManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x827DEDF8) is slot 11 of the vtable at 0x820098B8, as cNonGameBase's RetClassName.
#ifndef VFX_CPARTICLEEFFECTMANAGER_H
#define VFX_CPARTICLEEFFECTMANAGER_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cParticleEffectManager : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        int RetEffectId(const char *); // RuffKing name; CD2 0x827EB880
    public:
        // Out of line: CD2 0x82358538 (MakeNew calls it).
        cParticleEffectManager();

    private:
        unsigned char m_unmodelled7C[0x370 - 0x7C];

        CD2_LAYOUT_CHECKS(cParticleEffectManager, CD2_SIZE(cParticleEffectManager, 0x370))

    };
    extern cParticleEffectManager *g_pParticleEffectManager;
}

#endif // VFX_CPARTICLEEFFECTMANAGER_H
