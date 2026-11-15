#include "AI/cMissionBase.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#include "rws/attributes.h"
// AI::cAmbientEventMission (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8248DAE0) builds cClass(0x9FE8B, "cAmbientEventMission", 0x3B0); 0x3B0 is the size its registrar gives.
#ifndef AI_CAMBIENTEVENTMISSION_H
#define AI_CAMBIENTEVENTMISSION_H

#include "fun_runtime/class.h"

namespace AI
{
    class cAmbientEventMission : public AI::cMissionBase
    {
    public:
        virtual const char *RetClassName() const;
        // CD2 0x8248DA20 / 0x8248DA30: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAmbientEventMissionClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // AI_CAMBIENTEVENTMISSION_H
