// Runtime class inheritance registration. Names and parent/child lists from the reference cClass.h;
// CD2 0x82F76988 inlines these two push_back calls and RecursivelyAddParent in this order.
#ifndef FUN_RUNTIME_INHERITANCE_REGISTRAR_H
#define FUN_RUNTIME_INHERITANCE_REGISTRAR_H

#include "fun_runtime/class.h"

namespace Fun_Runtime
{
    class cInheritanceRegistrar
    {
    public:
        cInheritanceRegistrar(cClass &child, cClass &parent)
        {
            child.m_lParents.push_back(&parent);
            parent.m_lChildren.push_back(&child);
            child.RecursivelyAddParent(parent);
        }
    };
}

#endif
