// Audio::cWorldGameObject (Crackdown 2): STAND-IN. MakeNew 0x82837608 and RetClassName 0x82837648
// (vtable slot 7 of 0x820022DC) from CD2's initializer run; RuffKing names the class in cWorldGameObject.obj.
// No layout or other virtuals are modelled yet.
#ifndef AUDIO_CWORLDGAMEOBJECT_H
#define AUDIO_CWORLDGAMEOBJECT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Audio/cGameObject.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"

// Reconstruction update: method-only interface, not an allocation layout.
// Reference cWorldGameObject derives from cGameObject, CAttributeHandler,
// CEventHandler and DynamicAllocationPolicy. CD2 factory 0x82837608 converts
// the created object to its attribute interface at +0x90; the shared audio
// base layout remains incomplete. Primary table 0x820022DC adds RetClass,
// IsA and RetClassName after cGameObject's five slots (slots 5, 6 and 7).
// Initializer 0x830136C8 writes the descriptor pointer at 0x8392CAE0.

namespace Audio
{
    class cWorldGameObject : public cGameObject, public RWS::CAttributeHandler,
        public RWS::CEventHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        static const Fun_Runtime::cClass *ms_pcWorldGameObjectClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AUDIO_CWORLDGAMEOBJECT_H
