#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::CCarController (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8277ED80) builds cClass(0x929, "CCarController", 0xA30); 0xA30 is the size its registrar gives.
#ifndef UNKNOWN_CCARCONTROLLER_H
#define UNKNOWN_CCARCONTROLLER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class CCarController
    {
    public:
        // CD2 MakeNew (0x8277ec60) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class CCarControllerPrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline CCarControllerPrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}

            CD2_LAYOUT_CHECKS(CCarControllerPrototype, CD2_SIZE(CCarControllerPrototype, 0x70))
        };

        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pCCarControllerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CCARCONTROLLER_H
