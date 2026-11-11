// STAND-IN: CD2 names cGrappler; its constructor (0x82631BE0) calls cCWWeapon's at 0x82607FC8.
// StaticCreateClass (0x82631B40) gives size 0xA50. Own storage remains opaque; no instance is allocated here.
#ifndef UNKNOWN_CGRAPPLER_H
#define UNKNOWN_CGRAPPLER_H
#include "Equip/cCWWeapon.h"
namespace unknown
{
    class cGrappler : public Equip::cCWWeapon
    {
    public:
        cGrappler(GOM::cObjectPrototype *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGrapplerClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    private:
        unsigned char m_unmodelledA10[0xA50 - 0xA10];
        CD2_LAYOUT_CHECKS(cGrappler, CD2_SIZE(cGrappler, 0xA50))
    };
}
#endif
