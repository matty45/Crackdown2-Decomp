// AI::cTrainingAimTarget (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8247E848, MakeNew 0x8247E938, from its registrars in CD2's
// initializer run); RuffKing names the class in cTrainingAimTarget.obj. No layout or virtuals are modelled yet;
// base AI::cAttachableLight from CD2's inheritance registrar.
#ifndef AI_CTRAININGAIMTARGET_H
#define AI_CTRAININGAIMTARGET_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cAttachableLight.h"

namespace AI
{
    class cTrainingAimTarget : public cAttachableLight
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingAimTargetClass;
    };
}

#endif // AI_CTRAININGAIMTARGET_H
