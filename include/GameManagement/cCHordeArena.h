#ifndef GameManagement_cCHordeArena_H
#define GameManagement_cCHordeArena_H

#include "GameManagement/cGameModeArena.h"

namespace GameManagement
{
    class cCHordeProfile;
    class cCHordeArena : public cGameModeArena
    {
    protected:
        cCHordeProfile *m_pProfile;
    public:
        virtual const char *RetClassName() const;

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);
    };
}

#endif
