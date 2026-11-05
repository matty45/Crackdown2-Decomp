#ifndef GameManagement_cGameModeSpawnPoint_H
#define GameManagement_cGameModeSpawnPoint_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/mtx.h"

namespace GameManagement
{
    // STAND-IN: RuffKing base order and matrix name; CD2 MakeNew builds the identity at 0x20.
    class cGameModeSpawnPoint : public RWS::CSystemCommands, public RWS::CAttributeHandler
    {
    public:
        cGameModeSpawnPoint() {}
        virtual ~cGameModeSpawnPoint() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 primary slots 12..14; names/order agree with RuffKing's interface.
        virtual void Destruct();
        virtual bool IsActive() const;
        virtual int RetArenaIndex() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    protected:
        Fun_Runtime::Mtx m_Transform;
        CD2_LAYOUT_CHECKS(cGameModeSpawnPoint,
            CD2_SIZE(cGameModeSpawnPoint, 0x60)
            CD2_OFFSET(cGameModeSpawnPoint, m_Transform, 0x20))
    };
}

#endif
