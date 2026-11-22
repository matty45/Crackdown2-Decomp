#include "rws/attributes.h"
// unknown::cAudioLogContainer (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FF1518) registers "cAudioLogContainer" with MakeNew (0x8270FC88) and size 0xC4.
#ifndef UNKNOWN_CAUDIOLOGCONTAINER_H
#define UNKNOWN_CAUDIOLOGCONTAINER_H

#include "fun_runtime/class.h"

// Reconstruction update: method-only declaration, not an allocation layout.
// Factory 0x8270FC88 inlines the CAttributeHandler fields at +4..+14 and installs
// table 0x82139BC0. Its eleven framework slots are followed by RetClass, IsA,
// RetClassName and Destruct. There is no separate cRegisteredClass subobject.
// Initializer 0x82FF1468 creates descriptor (0x117, "cAudioLogContainer", 0xC4)
// and writes its pointer at 0x83849784; the static member name is ours.

namespace unknown
{
    class cAudioLogContainer : public RWS::CAttributeHandler
    {
    public:
        static const Fun_Runtime::cClass *ms_pcAudioLogContainerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // UNKNOWN_CAUDIOLOGCONTAINER_H
