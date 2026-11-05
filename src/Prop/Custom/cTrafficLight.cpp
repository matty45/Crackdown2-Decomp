// The shared cProp hierarchy now reproduces the inherited vptr stores exactly.

#include "gom/proto_registrar.h"
#include "Prop/cTrafficLight.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <stddef.h>
#include <new>

namespace Prop
{
    // CD2 0x827475C8 unlinks the light before invoking cProp's destructor.
    // The inherited secondary bases are still incomplete in cProp's stand-in layout.
    cTrafficLight::~cTrafficLight()
    {
        if (m_pNextActive)
            m_pNextActive->m_pPrevActive = m_pPrevActive;
        if (m_pPrevActive)
            m_pPrevActive->m_pNextActive = m_pNextActive;
        else if (this == ms_pFirstActive)
            ms_pFirstActive = m_pNextActive;
    }

    Fun_Runtime::RetVal cTrafficLight::cTrafficLightPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    const Fun_Runtime::cClass &cTrafficLight::RetClass() const
    {
        return *ms_pcTrafficLightClass;
    }

    bool cTrafficLight::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcTrafficLightClass->IsA(testClass);
    }

    RWS::CAttributeHandler *cTrafficLight::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cTrafficLight(prototype);
        return 0;
    }

    const char *cTrafficLight::RetClassName() const
    {
        return "cTrafficLight";
    }

    bool cTrafficLight::EnterRenderableState()
    {
        m_bFirstRender = true;
        return cProp::EnterRenderableState();
    }

    void cTrafficLight::UpdateRenderMatrix()
    {
        cProp::UpdateRenderMatrix();

        if (m_eCurrentColour != m_eNewColour || m_bFirstRender)
        {
            cTrafficLightPrototype *pPrototype = static_cast<cTrafficLightPrototype *>(m_pPrototype);
            unsigned int i = 0;
            while (i < pPrototype->m_nNumLights)
            {
                if (m_bLightActive && !m_bIsBroken)
                    AddLight(i, m_eNewColour);
                ++i;
            }

            m_bLightActive = true;
            m_bFirstRender = false;
            m_eCurrentColour = m_eNewColour;
        }
    }

    RWS::CAttributeHandler *cTrafficLight::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cTrafficLightPrototype *p = new cTrafficLightPrototype(packet);
        if (p)
        {
            p->m_nNumLights = 0;
            p->m_nTrafficLightType = -1;
            return p;
        }
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cTrafficLightRegistrar(
        "cTrafficLight", cTrafficLight::MakeNew, 0xE60, false);

    // CD2 0x82FFC3A8: class descriptor and placement factory.
    static GOM::cProtoRegistrar cTrafficLightSpawningRegistrar(
        cTrafficLight::StaticCreateClass(), cTrafficLight::SpawnFromPrototype);
}
