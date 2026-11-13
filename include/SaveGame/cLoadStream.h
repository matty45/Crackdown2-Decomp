// STAND-IN: interface from RuffKing's SaveGame/cLoadStream.h. CD2 zone Load
// callbacks inline ReadBool as a one-byte Read call to 0x82767390.
// Member names and complete layout follow the same reference header; CD2 Read
// confirms the loaded flag, buffer and chunk-bound/cursor offsets below.
#ifndef SAVEGAME_CLOADSTREAM_H
#define SAVEGAME_CLOADSTREAM_H

#include "fun_runtime/stringc.h"
#include "SaveGame/save_types.h"
#include "cd2/layout.h"

namespace SaveGame
{
    class cLoadStream
    {
    public:
        bool ReadBool(bool &value) { return Read(&value, sizeof(value)); }
        bool Read(void *data, unsigned int size);

    private:
        unsigned int m_nVersion;
        unsigned int m_nVersionMinCompatible;
        bool m_bLoaded;
        unsigned int m_nBufferSize;
        unsigned char *m_pBuffer;
        eSaveChunk m_CurrentChunk;
        unsigned int m_nNextChunk;
        unsigned int m_nCurrentSize;
        unsigned int m_nCurrentVersion;
        eSaveType m_nType;
        Fun_Runtime::cStringc m_sTempNarrowString;

        CD2_LAYOUT_CHECKS(cLoadStream,
            CD2_SIZE(cLoadStream, 0x44)
            CD2_OFFSET(cLoadStream, m_bLoaded, 0x8)
            CD2_OFFSET(cLoadStream, m_nBufferSize, 0xC)
            CD2_OFFSET(cLoadStream, m_pBuffer, 0x10)
            CD2_OFFSET(cLoadStream, m_nNextChunk, 0x18)
            CD2_OFFSET(cLoadStream, m_nCurrentSize, 0x1C))
    };
}

#endif
