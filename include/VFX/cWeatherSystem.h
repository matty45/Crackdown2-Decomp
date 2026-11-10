// VFX::cWeatherSystem (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827D7AC8, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeather.obj. No layout or virtuals are modelled yet.
#ifndef VFX_CWEATHERSYSTEM_H
#define VFX_CWEATHERSYSTEM_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "GDb/cDebugPageHandler.h"
#include "network/cReplicatedClass.h"
#include "network/netrole.h"
#include "SaveGame/cLoadSaveObject.h"

namespace VFX
{
    // Burn's base order agrees with CD2 constructor 0x827D7C90: event +0x18,
    // debug-page +0x1C, replication +0x20, network role +0x250, load/save +0x258.
    // Instance storage remains unmodelled.
    class cWeatherSystem : public RWS::CAttributeHandler, public RWS::CEventHandler,
        public GDb::cDebugPageHandler, public cReplicatedClass, public Network::cNetRoleObject,
        public SaveGame::cLoadSaveObject
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x82002DC4, slot 11.
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CWEATHERSYSTEM_H
