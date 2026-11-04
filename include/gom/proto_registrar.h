// STAND-IN: Burn GOMPrototype.h names the spawning registrar. CD2 constructor
// 0x82657690 installs a vptr, unlike Burn's empty registrar, and takes the class
// descriptor and placement factory. Gas canister initializer: 0x82FFACC8.
#ifndef GOM_PROTO_REGISTRAR_H
#define GOM_PROTO_REGISTRAR_H

#include "gom/object_prototype.h"
#include "fun_runtime/class.h"

namespace GOM
{
    struct cProtoRegistrar
    {
        cProtoRegistrar(const Fun_Runtime::cClass &,
            RWS::CAttributeHandler *(*)(cObjectPrototype *, void *));
        // The CD2 atexit body only restores this registrar vptr.
        virtual ~cProtoRegistrar() {}

        CD2_LAYOUT_CHECKS(cProtoRegistrar, CD2_SIZE(cProtoRegistrar, 4))
    };
}

#endif
