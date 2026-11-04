#ifndef Vehicle_cHelicopter_H
#define Vehicle_cHelicopter_H

#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Vehicle
{
    class cHelicopter : public RWS::CAttributeHandler
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype.
        cHelicopter();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x826B8D10 (MakeNew calls it with the packet).
        cHelicopter(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x4C0 - 0x18];

        CD2_LAYOUT_CHECKS(cHelicopter, CD2_SIZE(cHelicopter, 0x4C0))

    };
}

#endif
