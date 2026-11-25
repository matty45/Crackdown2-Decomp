#include "rws/attributes.h"
// WorldManager::cLOD4Environment: STAND-IN with reference base order; own storage is opaque.
// StaticCreateClass (0x82807868) builds cClass(0x199E, "cLOD4Environment", 0x2C0); 0x2C0 is the size its registrar gives.
#ifndef WORLDMANAGER_CLOD4ENVIRONMENT_H
#define WORLDMANAGER_CLOD4ENVIRONMENT_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "WorldManager/cFadeInOutInterface.h"
#include "fun_runtime/vectorip.h"
#include "fun_runtime/safedeletablepointer.h"
#include "editor/guid_event_handler.h"

namespace ResourceManager { class cResourceCatalogueEntry; }

namespace WorldManager
{
    class cStaticEnvironment;
    class cLOD4Environment : public cGameBase, public cFadeInOutInterface
    {
    public:
        // CD2 0x82807900 is called out of line without a packet.
        cLOD4Environment();
        virtual ~cLOD4Environment();
        // RuffKing names; CD2 0x82807FC8 (LockLOD) has two callers in this file, FadeDown and FadeUp.
        void LockLOD(cStaticEnvironment *pEnvBlock);
        bool AnyLOD3Fading() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 0x828077A0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82807858: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcLOD4EnvironmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // Reference member order; CD2 constructor 0x82807900 initializes the vector at +0x140.
        ResourceManager::cResourceCatalogueEntry *m_pResCatEntry;
        Fun_Runtime::cVectorip<Fun_Runtime::cSafeDeletablePointer<cStaticEnvironment>, 21> m_vpEnvBlocks;
        // CD2 HandleAttributes (0x82807E18) registers the GUID handler at +0x2A0.
        Editor::cGUIDEventHandler<cLOD4Environment> m_EventHandler;
        bool m_bBlockIsDisabled;
        CD2_LAYOUT_CHECKS(cLOD4Environment,
            CD2_SIZE(cLOD4Environment, 0x2C0)
            CD2_OFFSET(cLOD4Environment, m_pResCatEntry, 0x138)
            CD2_OFFSET(cLOD4Environment, m_vpEnvBlocks, 0x140)
            CD2_OFFSET(cLOD4Environment, m_EventHandler, 0x2A0)
            CD2_OFFSET(cLOD4Environment, m_bBlockIsDisabled, 0x2B4))
    };
}

#endif // WORLDMANAGER_CLOD4ENVIRONMENT_H
