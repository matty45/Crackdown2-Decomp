// Editor::cGUIDEventHandler<T>: links an entity to its RWS GUID for the editor.
// Reconstructed in CHARACTER/cNPCTintProfile.cpp and confirmed byte-exact there.
//  - Do NOT give cGUIDEventHandler<T> (or classes embedding it) a user-declared destructor: CD2's scalar deleting
//    destructors contain no vptr stores, which only happens with the implicit destructor.
//  - Register copies the GUID from a const reference into a local. That form is what reproduces CD2's copy scheduling.
//  - FindEntityInMap is static in CD2: every call site passes only the GUID's address in r3, with no linker object
//    (RuffKing's later build has it as a protected instance member). Callers reach it through the inline
//    cGUIDLinker<T>::LinkToObject (RuffKing name). RuffKing's LinkToObject takes the GUID by value, but in CD2 that form
//    breaks cFactionConfigData::HandleAttributes; a const reference copied into a local reproduces CD2's copy.
#ifndef EDITOR_GUID_EVENT_HANDLER_H
#define EDITOR_GUID_EVENT_HANDLER_H

#include "rws/attributes.h"

namespace Editor
{
    class cGUIDLinkerBase
    {
    public:
        cGUIDLinkerBase() {}
        virtual ~cGUIDLinkerBase();

    protected:
        static void *FindEntityInMap(const RWS::RWSGUID &);
    };

    template <class T>
    class cGUIDLinker : public cGUIDLinkerBase
    {
    public:
        static T *LinkToObject(const RWS::RWSGUID &id)
        {
            RWS::RWSGUID guid = id;
            return (T *)FindEntityInMap(guid);
        }
    };

    // The empty GUID the base constructor copies from (CD2 0x834146C4). The name is ours; the real name is unknown.
    // Not const: CD2 keeps it in writable .data, and under LTCG only a non-const global whose address escapes keeps
    // the constructor's vptr stores and load order as in CD2 (see tools/research/compiler_re/README.md).
    extern RWS::RWSGUID g_GUIDNull;

    class cGUIDEventHandlerBase : public cGUIDLinkerBase
    {
    private:
        RWS::RWSGUID m_GUID;

    protected:
        cGUIDEventHandlerBase() : m_GUID(g_GUIDNull) {}
        virtual ~cGUIDEventHandlerBase();
        void AddEntityToMap(const RWS::RWSGUID &, void *);
    };

    template <class T>
    class cGUIDEventHandler : public cGUIDEventHandlerBase
    {
    public:
        cGUIDEventHandler() {}
        void Register(T *pEntity, const RWS::RWSGUID &id)
        {
            RWS::RWSGUID guid = id;
            AddEntityToMap(guid, pEntity);
        }
    };
}

#endif // EDITOR_GUID_EVENT_HANDLER_H
