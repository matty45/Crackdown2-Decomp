#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_cDocksMission_H
#define AI_cDocksMission_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cDocksMission : public AI::cMission
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcDocksMissionClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    protected:
        // Size 0x450 from CD2's registrar (MakeNew allocates it); the fields after cMission are not modelled.
        unsigned int m_unmodelled3C0[(0x450 - 0x3C0) / 4];
        CD2_LAYOUT_CHECKS(cDocksMission, CD2_SIZE(cDocksMission, 0x450))
    };
}

#endif
