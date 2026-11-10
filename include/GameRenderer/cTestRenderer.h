// GameRenderer::cTestRenderer (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82667848, from its registrars in CD2's
// initializer run); RuffKing names the class in cTestRenderer.obj. No layout or virtuals are modelled yet.
#ifndef GAMERENDERER_CTESTRENDERER_H
#define GAMERENDERER_CTESTRENDERER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "GDb/cDebugPageHandler.h"

namespace GameRenderer
{
    // Burn's base order agrees with CD2 constructor 0x82667A90: the event
    // and debug-page subobjects are at +0x18 and +0x1C. Instance storage is not modelled.
    class cTestRenderer : public RWS::CAttributeHandler, public RWS::CEventHandler,
        public GDb::cDebugPageHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Primary table 0x8212E3A0, slot 11.
        virtual const char *RetClassName() const;
    };
}

#endif // GAMERENDERER_CTESTRENDERER_H
