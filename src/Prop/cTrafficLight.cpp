// src/Prop/cTrafficLight.cpp
//
// Class: cTrafficLight (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cTrafficlight.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code):
// include/ref/ruffking/Prop_cTrafficLight.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/cTrafficLight.cpp

#include "Prop/cTrafficLight.h"

namespace Prop
{
    void cTrafficLight::UpdateRenderMatrix()
    {
        cProp::UpdateRenderMatrix();

        if (m_eCurrentColour != m_eNewColour || m_bFirstRender)
        {
            cTrafficLightPrototype *pProto = static_cast<cTrafficLightPrototype *>(m_pPrototype);
            for (unsigned int i = 0; i < pProto->m_nNumLights; ++i)
            {
                if (m_bLightActive && !m_bIsBroken)
                    AddLight(i, m_eNewColour);
            }
            m_bLightActive = true;
            m_bFirstRender = false;
            m_eCurrentColour = m_eNewColour;
        }
    }
}
