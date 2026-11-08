// Anim::cAnimationParams (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824DF9F8, from its registrars in CD2's
// initializer run); RuffKing names the class in cAnimationParams.obj. No layout or virtuals are modelled yet;
// base Fun_Runtime::cScriptHost from CD2's inheritance registrar.
#ifndef ANIM_CANIMATIONPARAMS_H
#define ANIM_CANIMATIONPARAMS_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/scripthost.h"

namespace Anim
{
    class cAnimationParams : public Fun_Runtime::cScriptHost
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAnimationParamsClass;
    };
}

#endif // ANIM_CANIMATIONPARAMS_H
