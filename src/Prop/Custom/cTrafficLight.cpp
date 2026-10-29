#include "Prop/cTrafficLight.h"
#include "rws/classfactory.h"

namespace Prop
{
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
            p->m_unk500 = -1;
            return p;
        }
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cTrafficLightRegistrar(
        "cTrafficLight", cTrafficLight::MakeNew, 0xE60, false);
}
