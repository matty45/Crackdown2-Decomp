#ifndef Prop_cPintleFaceplate_H
#define Prop_cPintleFaceplate_H

#include "Prop/cProp.h"
#include "fun_runtime/class.h"

namespace Prop
{
    // STAND-IN: CD2 0x827453D8 invokes cProp's destructor; derived storage is not modelled yet.
    class cPintleFaceplate : public cProp
    {
    public:
        virtual ~cPintleFaceplate();
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcPintleFaceplateClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
