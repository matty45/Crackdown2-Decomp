// Anim::cAnimationParams (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824DF9F8, from its registrars in CD2's
// initializer run); RuffKing names its own fields. CD2 uses cScriptHost rather than the later cRegisteredClass
// base, moving those fields up 0x18; descriptor size 0x30 and the action-state record's two copies agree.
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
        cAnimationParams();
        virtual ~cAnimationParams();
    private:
        int m_nAnimID;
        float m_fPlayBackRate;
        float m_fBlendInTime;
        float m_fBlendOutTime;
        unsigned char m_flags; // packed animation options; bit names/positions are not modelled yet
        CD2_LAYOUT_CHECKS(cAnimationParams,
            CD2_SIZE(cAnimationParams, 0x30)
            CD2_OFFSET(cAnimationParams, m_nAnimID, 0x1C)
            CD2_OFFSET(cAnimationParams, m_fPlayBackRate, 0x20)
            CD2_OFFSET(cAnimationParams, m_fBlendInTime, 0x24)
            CD2_OFFSET(cAnimationParams, m_fBlendOutTime, 0x28)
            CD2_OFFSET(cAnimationParams, m_flags, 0x2C))
    };
}

#endif // ANIM_CANIMATIONPARAMS_H
