#ifndef unknown_cLaunchPadConfig_H
#define unknown_cLaunchPadConfig_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace unknown
{
    class cLaunchPadConfig : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        // CD2 primary table 0x82139E88 slot 12; reference name.
        virtual void Destruct();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2: cLaunchPadConfig's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82713E38
        // RuffKing/Burn names; CD2 handler 0x82713E38 accesses these seven globals.
        enum LoadParameterTypes
        {
            CMD_PadRadius = 0, CMD_LaunchVFX, CMD_TargetVFX, CMD_VFXScale,
            CMD_TrailVFX, CMD_TrailVFXScale, CMD_TrailVFXDelay
        };
        static float ms_fPadRadius;
        static int ms_nLaunchVFX;
        static int ms_nTargetVFX;
        static int ms_nTrailVFX;
        static float ms_fVFXScale;
        static float ms_fTrailVFXScale;
        static float ms_fTrailVFXDelay;

        CD2_LAYOUT_CHECKS(cLaunchPadConfig, CD2_SIZE(cLaunchPadConfig, 0x18))
    };
}

#endif
