// RWS::CClassFactory: registration of attribute-handler classes by name.
// Each handler class has a static CRegistrar whose dynamic initializer registers (class name, MakeNew, size), and
// whose destructor is registered with atexit. Confirmed by CHARACTER/cNPCTintProfile.cpp (byte-exact).
#ifndef RWS_CLASSFACTORY_H
#define RWS_CLASSFACTORY_H

#include "rws/attributes.h"

namespace RWS
{
    class CClassFactory
    {
    public:
        class CRegistrar
        {
        public:
            ~CRegistrar();
            CRegistrar(const char *, CAttributeHandler *(*)(const CAttributePacket &, bool), unsigned int, bool);
        };
    };
}

#endif // RWS_CLASSFACTORY_H
