#ifndef Prop_cPintleFaceplate_H
#define Prop_cPintleFaceplate_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Prop
{
    class cPintleFaceplate : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcPintleFaceplateClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
