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
    };
}

#endif // VFX_CLINKEDVFXSPAWNER_H
