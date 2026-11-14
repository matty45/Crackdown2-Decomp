// VFX::cWeatherSystem (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827D7AC8, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeather.obj. Size 0x3B0 (registrar, MakeNew's allocation); the
// instance fields after the bases are not modelled yet.
#ifndef VFX_CWEATHERSYSTEM_H
#define VFX_CWEATHERSYSTEM_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "GDb/cDebugPageHandler.h"
#include "network/cReplicatedClass.h"
#include "network/netrole.h"
#include "SaveGame/cLoadSaveObject.h"
#include "cd2/layout.h"

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
        // CD2 0x827D7C90; MakeNew passes it only this.
        cWeatherSystem();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x82002DC4, slot 11.
        virtual const char *RetClassName() const;
        virtual void HandleEvents(RWS::CMsg &);
        // CD2's replicated-class table 0x821516C8 supplies these formerly pure interface slots.
        virtual bool IsSequential() const;
        virtual bool IsOwnedLocally();
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;

    private:
        unsigned char m_unmodelled25C[0x3B0 - 0x25C];

        CD2_LAYOUT_CHECKS(cWeatherSystem,
            CD2_SIZE(cWeatherSystem, 0x3B0)
            CD2_OFFSET(cWeatherSystem, m_unmodelled25C, 0x25C))
    };
}

#endif // VFX_CWEATHERSYSTEM_H
