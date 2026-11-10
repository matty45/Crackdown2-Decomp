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
        // CD2: cCHordeArena's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool IsCHordeArena() const; // 16: 0x8288FB78
    };
}

#endif
