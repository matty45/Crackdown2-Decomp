// STAND-IN handler-table prefix. RuffKing provides m_apChunkHandlers and enum names.
// CD2 UI construction/destruction stores the options handler at +0x40 of the manager
// loaded from 0x83800FF0: type 0, chunk 16. Assertions are absent in CD2's inline stores.
#ifndef SAVEGAME_CSAVEGAMEMANAGER_H
#define SAVEGAME_CSAVEGAMEMANAGER_H
#include "cd2/layout.h"
namespace SaveGame
{
    class cLoadSaveObject;
    enum eSaveType { eSaveType_Options = 0 };
    enum eSaveChunk { eSaveChunk_Options = 16 };
    class cSaveGameManager
    {
        cLoadSaveObject *m_apChunkHandlers[3][24];
    public:
        void Register(eSaveType type, eSaveChunk chunk, cLoadSaveObject *object)
        {
            m_apChunkHandlers[type][chunk] = object;
        }
        void Unregister(eSaveType type, eSaveChunk chunk, cLoadSaveObject *)
        {
            m_apChunkHandlers[type][chunk] = 0;
        }
        CD2_LAYOUT_CHECKS(cSaveGameManager,
            CD2_OFFSET(cSaveGameManager, m_apChunkHandlers, 0))
    };
}
extern SaveGame::cSaveGameManager *g_pSaveGameManager;
namespace SaveGame
{
    inline void Register(eSaveType type, eSaveChunk chunk, cLoadSaveObject *object)
    {
        g_pSaveGameManager->Register(type, chunk, object);
    }
    inline void Unregister(eSaveType type, eSaveChunk chunk, cLoadSaveObject *object)
    {
        g_pSaveGameManager->Unregister(type, chunk, object);
    }
}
#endif
