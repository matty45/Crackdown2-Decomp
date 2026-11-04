// Shared Load/Save-only interface, extracted unchanged from UI/cUIControl.h.
// RuffKing evidence and CD2 UI vtables have no virtual destructor here.
#ifndef SAVEGAME_CLOADSAVEOBJECT_H
#define SAVEGAME_CLOADSAVEOBJECT_H
namespace SaveGame
{
    class cLoadStream;
    class cSaveStream;
    class cLoadSaveObject
    {
    public:
        // RuffKing's interface vtable contains Load and Save only; no virtual destructor.
        virtual void Load(cLoadStream *pStream) {}
        virtual void Save(cSaveStream *pStream) {}
    };
}
#endif
