#include "rws/attributes.h"
// WorldManager::cStaticEnvironment: STAND-IN with reference base order; own storage is opaque.
// StaticCreateClass (0x82808988) builds cClass(0x3, "cStaticEnvironment", 0x2E0); 0x2E0 is the size its registrar gives.
#ifndef WORLDMANAGER_CSTATICENVIRONMENT_H
#define WORLDMANAGER_CSTATICENVIRONMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cStaticBody.h"
#include "WorldManager/cFadeInOutInterface.h"
#include "fun_runtime/safedeletablepointer.h"

namespace WorldManager
{
    class cStaticEnvironment : public PHYSICS::cStaticBody, public ResourceManager::cStreamingResourceClient, public cFadeInOutInterface
    {
    public:
        // CD2 factory 0x82808918 passes the packet to constructor 0x822A3D30.
        cStaticEnvironment(const RWS::CAttributePacket &);
        virtual ~cStaticEnvironment();
        virtual bool HasLoadedResources(eResourcesType);
        virtual unsigned char RetResourceState();
        virtual void TermClump();
        virtual void ReCalculateResourceState();
        // CD2 0x82808970: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x828088A8 / 0x828088B8: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcStaticEnvironmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor installs the streaming/fade bases at +0x260/+0x26C before own fields.
        // Reference flags; CD2 constructor 0x822A3D30 clears all four bytes, and the resource query reads +0x287.
        bool m_bRenderable;
        bool m_bBlockIsDisabled;
        bool m_bInActiveRenderRegion;
        unsigned char m_nResourceState;
        // Reference member order, confirmed by CD2 constructor 0x822A3D30 and resource-state callback 0x828093C0.
        const char *m_sEnvBlockName;
        Fun_Runtime::cSafeDeletablePointer<RWS::CResource> m_apResources[4];
        unsigned char m_unmodelled2CC[0x2E0 - 0x2CC];
        CD2_LAYOUT_CHECKS(cStaticEnvironment,
            CD2_SIZE(cStaticEnvironment, 0x2E0)
            CD2_OFFSET(cStaticEnvironment, m_bRenderable, 0x284)
            CD2_OFFSET(cStaticEnvironment, m_bBlockIsDisabled, 0x285)
            CD2_OFFSET(cStaticEnvironment, m_bInActiveRenderRegion, 0x286)
            CD2_OFFSET(cStaticEnvironment, m_nResourceState, 0x287)
            CD2_OFFSET(cStaticEnvironment, m_sEnvBlockName, 0x288)
            CD2_OFFSET(cStaticEnvironment, m_apResources, 0x28C))
    };
}

#endif // WORLDMANAGER_CSTATICENVIRONMENT_H
