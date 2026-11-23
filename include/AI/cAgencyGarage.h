#include "rws/attributes.h"
// AI::cAgencyGarage (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82F8B1E8) registers "cAgencyGarage" with MakeNew (0x82479B80) and size 0x380.
#ifndef AI_CAGENCYGARAGE_H
#define AI_CAGENCYGARAGE_H

#include "rws/systemcommands.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"
#include "GDb/cDebugPageHandler.h"
#include "SaveGame/cLoadSaveObject.h"

// Reconstruction update: method-only declaration, not an allocation layout.
// CD2 constructor 0x82479BD8 and the reference cAgencyGarage header establish
// CAttributeHandler at +0, CEventHandler +0x18, cDebugPageHandler +0x1C and
// cLoadSaveObject +0x20. Table 0x82104630 is its registered-class/debug interface.
// Initializer 0x82F8B130 creates descriptor (0x9F3A3, "cAgencyGarage", 0x380)
// and stores its pointer at 0x8381CE2C.

namespace AI
{
    class cAgencyGarage : public RWS::CSystemCommands, public RWS::CAttributeHandler,
        public RWS::CEventHandler, public RWS::DynamicAllocationPolicy,
        public GDb::cDebugPageHandler, public SaveGame::cLoadSaveObject
    {
    public:
        static const Fun_Runtime::cClass *ms_pcAgencyGarageClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual ~cAgencyGarage();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CAGENCYGARAGE_H
